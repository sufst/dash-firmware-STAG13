/* Auto generated: Do not edit directly, instead add signals in Codegen/signal_mapping.yaml or update Codegen/can_rx_handlers.c.j2 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"

/* Include your generated cantools headers */
#include "can_t.h"
#include "can_s.h"

/* ==================================================================== */
/* Global Backing Variables for EEZ Studio                              */
/* ==================================================================== */


static int32_t g_vcu_rolling_counter = 0;
static int32_t g_vcu_ctrl_state = 0;
static int32_t g_vcu_current_mode = 0;
static int32_t g_vcu_requested_mode = 0;
static int32_t g_vcu_lc_state = 0;
static int32_t g_vcu_lc_fault = 0;
static bool g_vcu_lc_shadow_mode = false;
static bool g_vcu_lc_stationary = false;
static int32_t g_vcu_lc_arm_progress = 0;
static TickType_t g_vcu_launch_ctrl_rx_tick = 0;
static bool g_vcu_launch_ctrl_seen = false;

/* true once VCU_Launch_Ctrl has arrived within the last 500 ms */
static bool vcu_launch_ctrl_fresh(void)
{
    return g_vcu_launch_ctrl_seen &&
           (xTaskGetTickCount() - g_vcu_launch_ctrl_rx_tick) < pdMS_TO_TICKS(500);
}
static double g_bms_pack_inst_voltage = 0.0;
static double g_bms_pack_current = 0.0;
static double g_bms_pack_soc = 0.0;
static double g_pdm_input_10_voltage = 0.0;
static int32_t g_pm100_vsm_state = 0;
static double g_pm100_module_a = 0.0;
static double g_pm100_module_b = 0.0;
static double g_pm100_module_c = 0.0;
static double g_pm100_gate_driver_board = 0.0;
static double g_pm100_motor_temperature = 0.0;
static int32_t g_bms_high_temperature = 0;
static int32_t g_bms_average_temperature = 0;
static bool g_inverter = false;
static bool g_brakelight = false;
static bool g_pump = false;
static bool g_fan = false;
static double g_pdm_battery_voltage = 0.0;
static int32_t g_vcu_ctrl_error = 0;
static int32_t g_vcu_scs_error = 0;
static int32_t g_vcu_pm100_error = 0;
static int32_t g_vcu_rtcan1_error = 0;
static int32_t g_vcu_rtcan2_error = 0;
static int32_t g_vcu_canbc_error = 0;

static double g_wheel_fl_speed = 0.0;
static double g_wheel_fr_speed = 0.0;
static double g_wheel_rl_speed = 0.0;
static double g_wheel_rr_speed = 0.0;
static double g_vcu_sagl = 0.0;
static double g_vcu_apps = 0.0;
static double g_vcu_bps = 0.0;
static double g_lvbox_pwr = 0.0;
static int32_t g_vcu_apps1_raw = 0;
static int32_t g_vcu_apps2_raw = 0;
static int32_t g_vcu_bps_raw = 0;
static int32_t g_vcu_max_temp = 0;
static bool g_tap_estops = false;
static bool g_imd_fault = false;
static bool g_ams_fault = false;
static bool g_ts_detected = false;
static bool g_tap_latching = false;
static bool g_tap_hvd = false;
static bool g_tap_bots = false;
static bool g_tap_estop = false;
static bool g_tap_sdc_inertia = false;
static bool g_bspd_status = false;


/* ==================================================================== */
/* EEZ Studio Native Variable Interface (Getters & Setters)             */
/* ==================================================================== */


// Getter for vcu_rolling_counter
int32_t get_var_vcu_rolling_counter(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_rolling_counter;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_rolling_counter (No-op for read-only telemetry)
void set_var_vcu_rolling_counter(int32_t value)
{
    (void)value;
}
// Getter for vcu_ctrl_state
const char * get_var_vcu_ctrl_state(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_ctrl_state;
    taskEXIT_CRITICAL();
    switch (value)
    {
    case 0: return "TS Button Wait";
    case 1: return "Wait Neg AIR";
    case 2: return "Precharge Wait";
    case 3: return "R2D Wait";
    case 4: return "TS On";
    case 5: return "R2D Off";
    case 6: return "R2D Off Wait";
    case 7: return "TS Activation Failure";
    case 8: return "TS Run Fault";
    case 9: return "Spin";
    case 10: return "APPS SCS Fault";
    case 11: return "APPS BPS Fault";
    case 12: return "Sim Wait TS Off";
    case 13: return "Sim Wait TS On";
    case 14: return "Sim Wait R2D Off";
    case 15: return "Sim Wait R2D On";
    default: return "Unknown";
    }
}

// Setter for vcu_ctrl_state (No-op for read-only telemetry)
void set_var_vcu_ctrl_state(const char * value)
{
    (void)value;
}

// Raw value for vcu_ctrl_state, for C code that needs the number rather than the label
int32_t get_raw_vcu_ctrl_state(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_ctrl_state;
    taskEXIT_CRITICAL();
    return value;
}
// Getter for vcu_current_mode
const char * get_var_vcu_current_mode(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_current_mode;
    taskEXIT_CRITICAL();
    switch (value)
    {
    case 1: return "Endurance";
    case 2: return "Max";
    case 3: return "Launch_Ctrl";
    case 4: return "Crawl";
    case 5: return "Reverse";
    case 6: return "Remote_Ctrl";
    case 7: return "Undefined";
    case 8: return "Undefined";
    case 9: return "Undefined";
    case 10: return "Inverter_Prog";
    default: return "Unknown";
    }
}

// Setter for vcu_current_mode (No-op for read-only telemetry)
void set_var_vcu_current_mode(const char * value)
{
    (void)value;
}

// Raw value for vcu_current_mode, for C code that needs the number rather than the label
int32_t get_raw_vcu_current_mode(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_current_mode;
    taskEXIT_CRITICAL();
    return value;
}
// Getter for vcu_requested_mode
const char * get_var_vcu_requested_mode(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_requested_mode;
    taskEXIT_CRITICAL();
    switch (value)
    {
    case 1: return "Endurance";
    case 2: return "Max";
    case 3: return "Launch_Ctrl";
    case 4: return "Crawl";
    case 5: return "Reverse";
    case 6: return "Remote_Ctrl";
    case 7: return "Undefined";
    case 8: return "Undefined";
    case 9: return "Undefined";
    case 10: return "Inverter_Prog";
    default: return "Unknown";
    }
}

// Setter for vcu_requested_mode (No-op for read-only telemetry)
void set_var_vcu_requested_mode(const char * value)
{
    (void)value;
}

// Raw value for vcu_requested_mode, for C code that needs the number rather than the label
int32_t get_raw_vcu_requested_mode(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_requested_mode;
    taskEXIT_CRITICAL();
    return value;
}
// Getter for vcu_lc_state
const char * get_var_vcu_lc_state(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_state;
    bool fresh = vcu_launch_ctrl_fresh();
    taskEXIT_CRITICAL();

    if (!fresh)
    {
        return "No_Data";
    }
    switch (value)
    {
    case 0: return "Off";
    case 1: return "Armed";
    case 2: return "Active";
    case 3: return "Done";
    case 4: return "Fault";
    default: return "Unknown";
    }
}

// Setter for vcu_lc_state (No-op for read-only telemetry)
void set_var_vcu_lc_state(const char * value)
{
    (void)value;
}

// Raw value for vcu_lc_state, for C code that needs the number rather than the label
int32_t get_raw_vcu_lc_state(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_state;
    taskEXIT_CRITICAL();
    return value;
}
// Getter for vcu_lc_fault
const char * get_var_vcu_lc_fault(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_fault;
    bool fresh = vcu_launch_ctrl_fresh();
    taskEXIT_CRITICAL();

    if (!fresh)
    {
        return "No_Data";
    }
    switch (value)
    {
    case 0: return "None";
    case 1: return "Front_Stale";
    case 2: return "Front_Disagree";
    case 3: return "Motor_Reverse";
    case 4: return "Front_Ahead";
    case 5: return "Bad_Dt";
    default: return "Unknown";
    }
}

// Setter for vcu_lc_fault (No-op for read-only telemetry)
void set_var_vcu_lc_fault(const char * value)
{
    (void)value;
}

// Raw value for vcu_lc_fault, for C code that needs the number rather than the label
int32_t get_raw_vcu_lc_fault(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_fault;
    taskEXIT_CRITICAL();
    return value;
}
// Getter for vcu_lc_shadow_mode
bool get_var_vcu_lc_shadow_mode(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_shadow_mode;
    bool fresh = vcu_launch_ctrl_fresh();
    taskEXIT_CRITICAL();

    if (!fresh)
    {
        return false;
    }
    return value;
}

// Setter for vcu_lc_shadow_mode (No-op for read-only telemetry)
void set_var_vcu_lc_shadow_mode(bool value)
{
    (void)value;
}
// Getter for vcu_lc_stationary
bool get_var_vcu_lc_stationary(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_stationary;
    bool fresh = vcu_launch_ctrl_fresh();
    taskEXIT_CRITICAL();

    if (!fresh)
    {
        return false;
    }
    return value;
}

// Setter for vcu_lc_stationary (No-op for read-only telemetry)
void set_var_vcu_lc_stationary(bool value)
{
    (void)value;
}
// Getter for vcu_lc_arm_progress
int32_t get_var_vcu_lc_arm_progress(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_lc_arm_progress;
    bool fresh = vcu_launch_ctrl_fresh();
    taskEXIT_CRITICAL();

    if (!fresh)
    {
        return 0;
    }
    return value;
}

// Setter for vcu_lc_arm_progress (No-op for read-only telemetry)
void set_var_vcu_lc_arm_progress(int32_t value)
{
    (void)value;
}
// Getter for bms_pack_inst_voltage
double get_var_bms_pack_inst_voltage(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_bms_pack_inst_voltage;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for bms_pack_inst_voltage (No-op for read-only telemetry)
void set_var_bms_pack_inst_voltage(double value)
{
    (void)value;
}
// Getter for bms_pack_current
double get_var_bms_pack_current(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_bms_pack_current;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for bms_pack_current (No-op for read-only telemetry)
void set_var_bms_pack_current(double value)
{
    (void)value;
}
// Getter for bms_pack_soc
int32_t get_var_bms_pack_soc(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_bms_pack_soc;
    taskEXIT_CRITICAL();
    return (int32_t)lround(value);
}

// Setter for bms_pack_soc (No-op for read-only telemetry)
void set_var_bms_pack_soc(int32_t value)
{
    (void)value;
}
// Getter for pdm_input_10_voltage
double get_var_pdm_input_10_voltage(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pdm_input_10_voltage;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pdm_input_10_voltage (No-op for read-only telemetry)
void set_var_pdm_input_10_voltage(double value)
{
    (void)value;
}
// Getter for pm100_vsm_state
const char * get_var_pm100_vsm_state(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_pm100_vsm_state;
    taskEXIT_CRITICAL();
    switch (value)
    {
    case 0: return "VSM Start State";
    case 1: return "Pre-Charge Init state";
    case 2: return "pre-charge active state";
    case 3: return "pre-charge complete state";
    case 4: return "VSM wait state";
    case 5: return "VSM ready state";
    case 6: return "Motor Running State";
    case 7: return "blink fault code state";
    case 14: return "Shutdown state for Key Switch Mode 1";
    case 15: return "Reset the inverter";
    default: return "Unknown";
    }
}

// Setter for pm100_vsm_state (No-op for read-only telemetry)
void set_var_pm100_vsm_state(const char * value)
{
    (void)value;
}

// Raw value for pm100_vsm_state, for C code that needs the number rather than the label
int32_t get_raw_pm100_vsm_state(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_pm100_vsm_state;
    taskEXIT_CRITICAL();
    return value;
}
// Getter for pm100_module_a
double get_var_pm100_module_a(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pm100_module_a;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pm100_module_a (No-op for read-only telemetry)
void set_var_pm100_module_a(double value)
{
    (void)value;
}
// Getter for pm100_module_b
double get_var_pm100_module_b(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pm100_module_b;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pm100_module_b (No-op for read-only telemetry)
void set_var_pm100_module_b(double value)
{
    (void)value;
}
// Getter for pm100_module_c
double get_var_pm100_module_c(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pm100_module_c;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pm100_module_c (No-op for read-only telemetry)
void set_var_pm100_module_c(double value)
{
    (void)value;
}
// Getter for pm100_gate_driver_board
double get_var_pm100_gate_driver_board(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pm100_gate_driver_board;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pm100_gate_driver_board (No-op for read-only telemetry)
void set_var_pm100_gate_driver_board(double value)
{
    (void)value;
}
// Getter for pm100_motor_temperature
double get_var_pm100_motor_temperature(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pm100_motor_temperature;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pm100_motor_temperature (No-op for read-only telemetry)
void set_var_pm100_motor_temperature(double value)
{
    (void)value;
}
// Getter for bms_high_temperature
int32_t get_var_bms_high_temperature(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_bms_high_temperature;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for bms_high_temperature (No-op for read-only telemetry)
void set_var_bms_high_temperature(int32_t value)
{
    (void)value;
}
// Getter for bms_average_temperature
int32_t get_var_bms_average_temperature(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_bms_average_temperature;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for bms_average_temperature (No-op for read-only telemetry)
void set_var_bms_average_temperature(int32_t value)
{
    (void)value;
}
// Getter for inverter
bool get_var_inverter(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_inverter;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for inverter (No-op for read-only telemetry)
void set_var_inverter(bool value)
{
    (void)value;
}
// Getter for brakelight
bool get_var_brakelight(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_brakelight;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for brakelight (No-op for read-only telemetry)
void set_var_brakelight(bool value)
{
    (void)value;
}
// Getter for pump
bool get_var_pump(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_pump;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pump (No-op for read-only telemetry)
void set_var_pump(bool value)
{
    (void)value;
}
// Getter for fan
bool get_var_fan(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_fan;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for fan (No-op for read-only telemetry)
void set_var_fan(bool value)
{
    (void)value;
}
// Getter for pdm_battery_voltage
double get_var_pdm_battery_voltage(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_pdm_battery_voltage;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for pdm_battery_voltage (No-op for read-only telemetry)
void set_var_pdm_battery_voltage(double value)
{
    (void)value;
}
// Getter for vcu_ctrl_error
int32_t get_var_vcu_ctrl_error(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_ctrl_error;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_ctrl_error (No-op for read-only telemetry)
void set_var_vcu_ctrl_error(int32_t value)
{
    (void)value;
}
// Getter for vcu_scs_error
int32_t get_var_vcu_scs_error(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_scs_error;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_scs_error (No-op for read-only telemetry)
void set_var_vcu_scs_error(int32_t value)
{
    (void)value;
}
// Getter for vcu_pm100_error
int32_t get_var_vcu_pm100_error(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_pm100_error;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_pm100_error (No-op for read-only telemetry)
void set_var_vcu_pm100_error(int32_t value)
{
    (void)value;
}
// Getter for vcu_rtcan1_error
int32_t get_var_vcu_rtcan1_error(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_rtcan1_error;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_rtcan1_error (No-op for read-only telemetry)
void set_var_vcu_rtcan1_error(int32_t value)
{
    (void)value;
}
// Getter for vcu_rtcan2_error
int32_t get_var_vcu_rtcan2_error(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_rtcan2_error;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_rtcan2_error (No-op for read-only telemetry)
void set_var_vcu_rtcan2_error(int32_t value)
{
    (void)value;
}
// Getter for vcu_canbc_error
int32_t get_var_vcu_canbc_error(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_canbc_error;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_canbc_error (No-op for read-only telemetry)
void set_var_vcu_canbc_error(int32_t value)
{
    (void)value;
}

// Getter for wheel_fl_speed
double get_var_wheel_fl_speed(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_wheel_fl_speed;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for wheel_fl_speed (No-op for read-only telemetry)
void set_var_wheel_fl_speed(double value)
{
    (void)value;
}
// Getter for wheel_fr_speed
double get_var_wheel_fr_speed(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_wheel_fr_speed;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for wheel_fr_speed (No-op for read-only telemetry)
void set_var_wheel_fr_speed(double value)
{
    (void)value;
}
// Getter for wheel_rl_speed
double get_var_wheel_rl_speed(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_wheel_rl_speed;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for wheel_rl_speed (No-op for read-only telemetry)
void set_var_wheel_rl_speed(double value)
{
    (void)value;
}
// Getter for wheel_rr_speed
double get_var_wheel_rr_speed(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_wheel_rr_speed;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for wheel_rr_speed (No-op for read-only telemetry)
void set_var_wheel_rr_speed(double value)
{
    (void)value;
}
// Getter for vcu_sagl
double get_var_vcu_sagl(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_vcu_sagl;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_sagl (No-op for read-only telemetry)
void set_var_vcu_sagl(double value)
{
    (void)value;
}
// Getter for vcu_apps
double get_var_vcu_apps(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_vcu_apps;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_apps (No-op for read-only telemetry)
void set_var_vcu_apps(double value)
{
    (void)value;
}
// Getter for vcu_bps
double get_var_vcu_bps(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_vcu_bps;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_bps (No-op for read-only telemetry)
void set_var_vcu_bps(double value)
{
    (void)value;
}
// Getter for lvbox_pwr
double get_var_lvbox_pwr(void)
{
    double value;

    taskENTER_CRITICAL();
    value = g_lvbox_pwr;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for lvbox_pwr (No-op for read-only telemetry)
void set_var_lvbox_pwr(double value)
{
    (void)value;
}
// Getter for vcu_apps1_raw
int32_t get_var_vcu_apps1_raw(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_apps1_raw;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_apps1_raw (No-op for read-only telemetry)
void set_var_vcu_apps1_raw(int32_t value)
{
    (void)value;
}
// Getter for vcu_apps2_raw
int32_t get_var_vcu_apps2_raw(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_apps2_raw;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_apps2_raw (No-op for read-only telemetry)
void set_var_vcu_apps2_raw(int32_t value)
{
    (void)value;
}
// Getter for vcu_bps_raw
int32_t get_var_vcu_bps_raw(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_bps_raw;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_bps_raw (No-op for read-only telemetry)
void set_var_vcu_bps_raw(int32_t value)
{
    (void)value;
}
// Getter for vcu_max_temp
int32_t get_var_vcu_max_temp(void)
{
    int32_t value;

    taskENTER_CRITICAL();
    value = g_vcu_max_temp;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for vcu_max_temp (No-op for read-only telemetry)
void set_var_vcu_max_temp(int32_t value)
{
    (void)value;
}
// Getter for tap_estops
bool get_var_tap_estops(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_tap_estops;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for tap_estops (No-op for read-only telemetry)
void set_var_tap_estops(bool value)
{
    (void)value;
}
// Getter for imd_fault
bool get_var_imd_fault(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_imd_fault;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for imd_fault (No-op for read-only telemetry)
void set_var_imd_fault(bool value)
{
    (void)value;
}
// Getter for ams_fault
bool get_var_ams_fault(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_ams_fault;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for ams_fault (No-op for read-only telemetry)
void set_var_ams_fault(bool value)
{
    (void)value;
}
// Getter for ts_detected
bool get_var_ts_detected(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_ts_detected;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for ts_detected (No-op for read-only telemetry)
void set_var_ts_detected(bool value)
{
    (void)value;
}
// Getter for tap_latching
bool get_var_tap_latching(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_tap_latching;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for tap_latching (No-op for read-only telemetry)
void set_var_tap_latching(bool value)
{
    (void)value;
}
// Getter for tap_hvd
bool get_var_tap_hvd(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_tap_hvd;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for tap_hvd (No-op for read-only telemetry)
void set_var_tap_hvd(bool value)
{
    (void)value;
}
// Getter for tap_bots
bool get_var_tap_bots(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_tap_bots;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for tap_bots (No-op for read-only telemetry)
void set_var_tap_bots(bool value)
{
    (void)value;
}
// Getter for tap_estop
bool get_var_tap_estop(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_tap_estop;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for tap_estop (No-op for read-only telemetry)
void set_var_tap_estop(bool value)
{
    (void)value;
}
// Getter for tap_sdc_inertia
bool get_var_tap_sdc_inertia(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_tap_sdc_inertia;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for tap_sdc_inertia (No-op for read-only telemetry)
void set_var_tap_sdc_inertia(bool value)
{
    (void)value;
}
// Getter for bspd_status
bool get_var_bspd_status(void)
{
    bool value;

    taskENTER_CRITICAL();
    value = g_bspd_status;
    taskEXIT_CRITICAL();
    return value;
}

// Setter for bspd_status (No-op for read-only telemetry)
void set_var_bspd_status(bool value)
{
    (void)value;
}


/* ==================================================================== */
/* CAN Message Handlers                                                 */
/* ==================================================================== */


/**
 * @brief Decode and map RX messages for CAN_T
 */
void can_t_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length)
{
    switch (id)
    {
    case CAN_T_VCU_STATE_FRAME_ID:
    {
        struct can_t_vcu_state_t payload;
        if (can_t_vcu_state_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_vcu_rolling_counter = (int32_t)can_t_vcu_state_vcu_rolling_counter_decode(payload.vcu_rolling_counter);
            g_vcu_ctrl_state = (int32_t)can_t_vcu_state_vcu_ctrl_state_decode(payload.vcu_ctrl_state);
            g_vcu_current_mode = (int32_t)can_t_vcu_state_vcu_current_mode_decode(payload.vcu_current_mode);
            g_vcu_requested_mode = (int32_t)can_t_vcu_state_vcu_requested_mode_decode(payload.vcu_requested_mode);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_VCU_LAUNCH_CTRL_FRAME_ID:
    {
        struct can_t_vcu_launch_ctrl_t payload;
        if (can_t_vcu_launch_ctrl_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_vcu_lc_state = (int32_t)can_t_vcu_launch_ctrl_vcu_lc_state_decode(payload.vcu_lc_state);
            g_vcu_lc_fault = (int32_t)can_t_vcu_launch_ctrl_vcu_lc_fault_decode(payload.vcu_lc_fault);
            g_vcu_lc_shadow_mode = (bool)can_t_vcu_launch_ctrl_vcu_lc_shadow_mode_decode(payload.vcu_lc_shadow_mode);
            g_vcu_lc_stationary = (bool)can_t_vcu_launch_ctrl_vcu_lc_stationary_decode(payload.vcu_lc_stationary);
            g_vcu_lc_arm_progress = (int32_t)can_t_vcu_launch_ctrl_vcu_lc_arm_progress_decode(payload.vcu_lc_arm_progress);
            g_vcu_launch_ctrl_rx_tick = xTaskGetTickCount();
            g_vcu_launch_ctrl_seen = true;
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_BMS_PACK_STATE_FRAME_ID:
    {
        struct can_t_bms_pack_state_t payload;
        if (can_t_bms_pack_state_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_bms_pack_inst_voltage = (double)can_t_bms_pack_state_bms_pack_inst_voltage_decode(payload.bms_pack_inst_voltage);
            g_bms_pack_current = (double)can_t_bms_pack_state_bms_pack_current_decode(payload.bms_pack_current);
            g_bms_pack_soc = (double)can_t_bms_pack_state_bms_pack_soc_decode(payload.bms_pack_soc);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_PDM_IN_VOLTAGE_FRAME_ID:
    {
        struct can_t_pdm_in_voltage_t payload;
        if (can_t_pdm_in_voltage_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            if (payload.pdm_in_voltage_compound_id == 1)
            {
                g_pdm_input_10_voltage = (double)can_t_pdm_in_voltage_pdm_input_10_voltage_decode(payload.pdm_input_10_voltage);
            }
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_PM100_INTERNAL_STATES_FRAME_ID:
    {
        struct can_t_pm100_internal_states_t payload;
        if (can_t_pm100_internal_states_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_pm100_vsm_state = (int32_t)can_t_pm100_internal_states_pm100_vsm_state_decode(payload.pm100_vsm_state);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_PM100_TEMPERATURE_SET_1_FRAME_ID:
    {
        struct can_t_pm100_temperature_set_1_t payload;
        if (can_t_pm100_temperature_set_1_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_pm100_module_a = (double)can_t_pm100_temperature_set_1_pm100_module_a_decode(payload.pm100_module_a);
            g_pm100_module_b = (double)can_t_pm100_temperature_set_1_pm100_module_b_decode(payload.pm100_module_b);
            g_pm100_module_c = (double)can_t_pm100_temperature_set_1_pm100_module_c_decode(payload.pm100_module_c);
            g_pm100_gate_driver_board = (double)can_t_pm100_temperature_set_1_pm100_gate_driver_board_decode(payload.pm100_gate_driver_board);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_PM100_TEMPERATURE_SET_3_FRAME_ID:
    {
        struct can_t_pm100_temperature_set_3_t payload;
        if (can_t_pm100_temperature_set_3_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_pm100_motor_temperature = (double)can_t_pm100_temperature_set_3_pm100_motor_temperature_decode(payload.pm100_motor_temperature);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_BMS_CELL_STATE_FRAME_ID:
    {
        struct can_t_bms_cell_state_t payload;
        if (can_t_bms_cell_state_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_bms_high_temperature = (int32_t)can_t_bms_cell_state_bms_high_temperature_decode(payload.bms_high_temperature);
            g_bms_average_temperature = (int32_t)can_t_bms_cell_state_bms_average_temperature_decode(payload.bms_average_temperature);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_VCU_PDM_FRAME_ID:
    {
        struct can_t_vcu_pdm_t payload;
        if (can_t_vcu_pdm_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_inverter = (bool)can_t_vcu_pdm_inverter_decode(payload.inverter);
            g_brakelight = (bool)can_t_vcu_pdm_brakelight_decode(payload.brakelight);
            g_pump = (bool)can_t_vcu_pdm_pump_decode(payload.pump);
            g_fan = (bool)can_t_vcu_pdm_fan_decode(payload.fan);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_PDM_STATE_FRAME_ID:
    {
        struct can_t_pdm_state_t payload;
        if (can_t_pdm_state_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            if (payload.pdm_state_compound_id == 3)
            {
                g_pdm_battery_voltage = (double)can_t_pdm_state_pdm_battery_voltage_decode(payload.pdm_battery_voltage);
            }
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_T_VCU_ERROR_FRAME_ID:
    {
        struct can_t_vcu_error_t payload;
        if (can_t_vcu_error_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_vcu_ctrl_error = (int32_t)can_t_vcu_error_vcu_ctrl_error_decode(payload.vcu_ctrl_error);
            g_vcu_scs_error = (int32_t)can_t_vcu_error_vcu_scs_error_decode(payload.vcu_scs_error);
            g_vcu_pm100_error = (int32_t)can_t_vcu_error_vcu_pm100_error_decode(payload.vcu_pm100_error);
            g_vcu_rtcan1_error = (int32_t)can_t_vcu_error_vcu_rtcan1_error_decode(payload.vcu_rtcan1_error);
            g_vcu_rtcan2_error = (int32_t)can_t_vcu_error_vcu_rtcan2_error_decode(payload.vcu_rtcan2_error);
            g_vcu_canbc_error = (int32_t)can_t_vcu_error_vcu_canbc_error_decode(payload.vcu_canbc_error);
            taskEXIT_CRITICAL();
        }
        break;
    }

    default:
        // Unhandled frame ID on CAN_T
        break;
    }
}

/**
 * @brief Decode and map RX messages for CAN_S
 */
void can_s_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length)
{
    switch (id)
    {
    case CAN_S_WHEEL_SPEEDS_FRAME_ID:
    {
        struct can_s_wheel_speeds_t payload;
        if (can_s_wheel_speeds_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_wheel_fl_speed = (double)can_s_wheel_speeds_wheel_fl_speed_decode(payload.wheel_fl_speed);
            g_wheel_fr_speed = (double)can_s_wheel_speeds_wheel_fr_speed_decode(payload.wheel_fr_speed);
            g_wheel_rl_speed = (double)can_s_wheel_speeds_wheel_rl_speed_decode(payload.wheel_rl_speed);
            g_wheel_rr_speed = (double)can_s_wheel_speeds_wheel_rr_speed_decode(payload.wheel_rr_speed);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_VCU_SENSORS_FRAME_ID:
    {
        struct can_s_vcu_sensors_t payload;
        if (can_s_vcu_sensors_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_vcu_sagl = (double)can_s_vcu_sensors_vcu_sagl_decode(payload.vcu_sagl);
            g_vcu_apps = (double)can_s_vcu_sensors_vcu_apps_decode(payload.vcu_apps);
            g_vcu_bps = (double)can_s_vcu_sensors_vcu_bps_decode(payload.vcu_bps);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_LV_BOX_ANALOG_FRAME_ID:
    {
        struct can_s_lv_box_analog_t payload;
        if (can_s_lv_box_analog_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_lvbox_pwr = (double)can_s_lv_box_analog_lvbox_pwr_decode(payload.lvbox_pwr);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_VCU_SENSORS_RAW_FRAME_ID:
    {
        struct can_s_vcu_sensors_raw_t payload;
        if (can_s_vcu_sensors_raw_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_vcu_apps1_raw = (int32_t)can_s_vcu_sensors_raw_vcu_apps1_raw_decode(payload.vcu_apps1_raw);
            g_vcu_apps2_raw = (int32_t)can_s_vcu_sensors_raw_vcu_apps2_raw_decode(payload.vcu_apps2_raw);
            g_vcu_bps_raw = (int32_t)can_s_vcu_sensors_raw_vcu_bps_raw_decode(payload.vcu_bps_raw);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_VCU_TEMPS_FRAME_ID:
    {
        struct can_s_vcu_temps_t payload;
        if (can_s_vcu_temps_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_vcu_max_temp = (int32_t)can_s_vcu_temps_vcu_max_temp_decode(payload.vcu_max_temp);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_LV_BOX_DIGITAL_FRAME_ID:
    {
        struct can_s_lv_box_digital_t payload;
        if (can_s_lv_box_digital_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_tap_estops = (bool)can_s_lv_box_digital_tap_estops_decode(payload.tap_estops);
            g_imd_fault = (bool)can_s_lv_box_digital_imd_fault_decode(payload.imd_fault);
            g_ams_fault = (bool)can_s_lv_box_digital_ams_fault_decode(payload.ams_fault);
            g_ts_detected = (bool)can_s_lv_box_digital_ts_detected_decode(payload.ts_detected);
            g_tap_latching = (bool)can_s_lv_box_digital_tap_latching_decode(payload.tap_latching);
            g_tap_hvd = (bool)can_s_lv_box_digital_tap_hvd_decode(payload.tap_hvd);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_DASH_SENSORS_DIGITAL_FRAME_ID:
    {
        struct can_s_dash_sensors_digital_t payload;
        if (can_s_dash_sensors_digital_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_tap_bots = (bool)can_s_dash_sensors_digital_tap_bots_decode(payload.tap_bots);
            g_tap_estop = (bool)can_s_dash_sensors_digital_tap_estop_decode(payload.tap_estop);
            g_tap_sdc_inertia = (bool)can_s_dash_sensors_digital_tap_sdc_inertia_decode(payload.tap_sdc_inertia);
            taskEXIT_CRITICAL();
        }
        break;
    }
    case CAN_S_PEDAL_BOX_DIGITAL_FRAME_ID:
    {
        struct can_s_pedal_box_digital_t payload;
        if (can_s_pedal_box_digital_unpack(&payload, data, length) == 0)
        {
            taskENTER_CRITICAL();
            g_bspd_status = (bool)can_s_pedal_box_digital_bspd_status_decode(payload.bspd_status);
            taskEXIT_CRITICAL();
        }
        break;
    }

    default:
        // Unhandled frame ID on CAN_S
        break;
    }
}
