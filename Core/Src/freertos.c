/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>

#include "can.h"
#include "ltdc.h"
#include "ui.h"
#include "screen_select.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__
#define USED __attribute__((used))
#else
#define USED
#endif
 
volatile const int USED uxTopUsedPriority = configMAX_PRIORITIES - 1;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for canRXTask */
osThreadId_t canRXTaskHandle;
const osThreadAttr_t canRXTask_attributes = {
  .name = "canRXTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

#define DASH_LCD_HOR_RES 800U
#define DASH_LCD_VER_RES 480U
#define DASH_LCD_FB0_ADDR ((lv_color_t *) 0xC0000000U)
#define DASH_LCD_FB1_ADDR ((lv_color_t *) (0xC0000000U + (DASH_LCD_HOR_RES * DASH_LCD_VER_RES * sizeof(lv_color_t))))

/* Given by HAL_LTDC_ReloadEventCallback() once a flush's FBStartAdress swap
   has actually landed at the vertical blanking interval -- only then is it
   safe to let LVGL start drawing into the buffer that was just displayed. */
static osSemaphoreId_t lcd_reload_sem;

void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc_arg)
{
  (void) hltdc_arg;
  osSemaphoreRelease(lcd_reload_sem);
}

static void dash_lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
  (void) area;
  (void) color_p;

  /* In direct_mode, flush_cb is invoked once per separate invalidated
     region within a single refresh cycle, but the active buffer only
     actually swaps after the last one (see draw_buf_flush() in
     lv_refr.c). Presenting the buffer to the LTDC on every intermediate
     call would flash partially-drawn frames onto the live scan-out, so
     only push/wait on the final flush of the cycle. */
  if (!lv_disp_flush_is_last(disp_drv))
  {
    lv_disp_flush_ready(disp_drv);
    return;
  }

  /* Hand the just-rendered (off-screen) buffer to the LTDC and swap at the
     next vblank instead of mid-scan, then wait for that swap to complete
     before telling LVGL the flush is done -- this is what actually stops
     the tearing/flicker, on top of no longer sharing one buffer between
     the renderer and the live scan-out. */
  HAL_LTDC_SetAddress_NoReload(&hltdc, (uint32_t) color_p, 0);
  HAL_LTDC_Reload(&hltdc, LTDC_RELOAD_VERTICAL_BLANKING);
  osSemaphoreAcquire(lcd_reload_sem, osWaitForever);

  lv_disp_flush_ready(disp_drv);
}

/* Implemented in can.c; not declared in can.h to keep can.h HAL-callback-free */
HAL_StatusTypeDef can_bus_init(CAN_HandleTypeDef *can_s_h, CAN_HandleTypeDef *can_t_h);
void can_rx_queue_init(void);
bool can_rx_process_pending(uint32_t timeout_ms);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* Must exist before osKernelStart() -- the CAN RX ISR (see can.c) can start
     pushing frames onto it as soon as can_bus_init() enables interrupts,
     which happens from StartDefaultTask() right after the scheduler starts. */
  can_rx_queue_init();
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of canRXTask */
  canRXTaskHandle = osThreadNew(StartTask02, NULL, &canRXTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */

  if (can_bus_init(&hcan1, &hcan2) != HAL_OK)
  {
    /* Do not call Error_Handler() -- losing a CAN bus shouldn't halt the
       whole dashboard. Inspect can_bus_get_error() to diagnose. */
  }

  lv_init();

  lcd_reload_sem = osSemaphoreNew(1, 0, NULL);

  static lv_disp_draw_buf_t draw_buf;
  lv_disp_draw_buf_init(&draw_buf, DASH_LCD_FB0_ADDR, DASH_LCD_FB1_ADDR, DASH_LCD_HOR_RES * DASH_LCD_VER_RES);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = DASH_LCD_HOR_RES;
  disp_drv.ver_res = DASH_LCD_VER_RES;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.flush_cb = dash_lvgl_flush_cb;
  disp_drv.direct_mode = 1;
  disp_drv.full_refresh = 0;
  lv_disp_drv_register(&disp_drv);

  ui_init();
  eez_flow_set_theme(DASH_THEME);

  /* Infinite loop */
  for(;;)
  {
    lv_tick_inc(5);
    screen_select_tick();
    ui_tick();
    lv_timer_handler();
    osDelay(5);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the canRXTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    can_rx_process_pending(osWaitForever);
  }
  /* USER CODE END StartTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

