#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SKIDPAD = 2,
    SCREEN_ID_ACCEL = 3,
    SCREEN_ID_DYNO = 4,
    SCREEN_ID_DEBUG = 5,
    SCREEN_ID_SPONSORS = 6,
    _SCREEN_ID_LAST = 6
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *skidpad;
    lv_obj_t *accel;
    lv_obj_t *dyno;
    lv_obj_t *debug;
    lv_obj_t *sponsors;
    lv_obj_t *lvbox_pwr;
    lv_obj_t *vcu_state;
    lv_obj_t *inv_state;
    lv_obj_t *pdm_11;
    lv_obj_t *obj0;
    lv_obj_t *lap_number;
    lv_obj_t *inverter_on;
    lv_obj_t *inverter_off;
    lv_obj_t *pumps_on;
    lv_obj_t *pumps_off;
    lv_obj_t *fans_on;
    lv_obj_t *fans_off;
    lv_obj_t *tc_on;
    lv_obj_t *tc_off;
    lv_obj_t *battery_ok;
    lv_obj_t *battery_warn;
    lv_obj_t *battery_crit;
    lv_obj_t *motor_ok;
    lv_obj_t *motor_warn;
    lv_obj_t *motor_cit;
    lv_obj_t *inverter_ok;
    lv_obj_t *inverter_warn;
    lv_obj_t *inverter_cit;
    lv_obj_t *obj1;
    lv_obj_t *inverter_temp;
    lv_obj_t *inverter_temp_4;
    lv_obj_t *inverter_temp_5;
    lv_obj_t *motor_temp;
    lv_obj_t *inverter_temp_6;
    lv_obj_t *battery_temp;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *soc_percent;
    lv_obj_t *soc_percent_warn;
    lv_obj_t *soc_percent_crit;
    lv_obj_t *mode;
    lv_obj_t *inverter_switch_label;
    lv_obj_t *pumps_switch_label;
    lv_obj_t *fans_switch_label;
    lv_obj_t *tc_switch_label;
    lv_obj_t *startup_instructions;
    lv_obj_t *soc_target_text;
    lv_obj_t *soc_target_text_neg;
    lv_obj_t *soc;
    lv_obj_t *soc__;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *lap;
    lv_obj_t *skidpad_lvbox_pwr;
    lv_obj_t *skidpad_vcu_state;
    lv_obj_t *skidpad_inv_state;
    lv_obj_t *skidpad_pdm_11;
    lv_obj_t *obj12;
    lv_obj_t *skidpad_inverter_on;
    lv_obj_t *skidpad_inverter_off;
    lv_obj_t *skidpad_pumps_on;
    lv_obj_t *skidpad_pumps_off;
    lv_obj_t *skidpad_fans_on;
    lv_obj_t *skidpad_fans_off;
    lv_obj_t *skidpad_tc_on;
    lv_obj_t *skidpad_tc_off;
    lv_obj_t *skidpad_battery_ok;
    lv_obj_t *skidpad_battery_warn;
    lv_obj_t *skidpad_battery_crit;
    lv_obj_t *skidpad_motor_ok;
    lv_obj_t *skidpad_motor_warn;
    lv_obj_t *skidpad_motor_cit;
    lv_obj_t *skidpad_inverter_ok;
    lv_obj_t *skidpad_inverter_warn;
    lv_obj_t *skidpad_inverter_cit;
    lv_obj_t *obj13;
    lv_obj_t *skidpad_inverter_temp;
    lv_obj_t *skidpad_inverter_temp_4;
    lv_obj_t *skidpad_inverter_temp_5;
    lv_obj_t *skidpad_motor_temp;
    lv_obj_t *skidpad_inverter_temp_6;
    lv_obj_t *skidpad_battery_temp;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *skidpad_soc_percent;
    lv_obj_t *skidpad_soc_percent_warn;
    lv_obj_t *skidpad_soc_percent_crit;
    lv_obj_t *skidpad_mode;
    lv_obj_t *skidpad_inverter_switch_label;
    lv_obj_t *skidpad_pumps_switch_label;
    lv_obj_t *skidpad_fans_switch_label;
    lv_obj_t *skidpad_tc_switch_label;
    lv_obj_t *skidpad_startup_instructions;
    lv_obj_t *skidpad_soc;
    lv_obj_t *obj22;
    lv_obj_t *accel_inv_state;
    lv_obj_t *accel_pdm_11;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *accel_inverter_on;
    lv_obj_t *accel_inverter_off;
    lv_obj_t *accel_pumps_on;
    lv_obj_t *accel_pumps_off;
    lv_obj_t *accel_fans_on;
    lv_obj_t *accel_fans_off;
    lv_obj_t *accel_tc_on;
    lv_obj_t *accel_tc_off;
    lv_obj_t *accel_battery_ok;
    lv_obj_t *accel_battery_warn;
    lv_obj_t *accel_battery_crit;
    lv_obj_t *accel_motor_ok;
    lv_obj_t *accel_motor_warn;
    lv_obj_t *accel_motor_cit;
    lv_obj_t *accel_inverter_ok;
    lv_obj_t *accel_inverter_warn;
    lv_obj_t *accel_inverter_cit;
    lv_obj_t *obj25;
    lv_obj_t *accel_inverter_temp;
    lv_obj_t *accel_inverter_temp_4;
    lv_obj_t *accel_inverter_temp_5;
    lv_obj_t *accel_motor_temp;
    lv_obj_t *accel_inverter_temp_6;
    lv_obj_t *accel_battery_temp;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *accel_soc_percent;
    lv_obj_t *accel_soc_percent_warn;
    lv_obj_t *accel_soc_percent_crit;
    lv_obj_t *accel_mode;
    lv_obj_t *accel_inverter_switch_label;
    lv_obj_t *accel_pumps_switch_label;
    lv_obj_t *accel_fans_switch_label;
    lv_obj_t *accel_tc_switch_label;
    lv_obj_t *obj33;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *accel_launch_header;
    lv_obj_t *obj36;
    lv_obj_t *accel_startup_instructions;
    lv_obj_t *accel_lc_status;
    lv_obj_t *accel_lc_status_go;
    lv_obj_t *accel_lc_status_fault;
    lv_obj_t *accel_lc_hint;
    lv_obj_t *accel_lc_arm_bar;
    lv_obj_t *accel_lc_fault_reason;
    lv_obj_t *accel_lc_shadow;
    lv_obj_t *accel_slip_warn;
    lv_obj_t *accel_speed;
    lv_obj_t *accel_slip;
    lv_obj_t *accel_vcu_state;
    lv_obj_t *accel_lvbox_pwr;
    lv_obj_t *soc_label;
    lv_obj_t *dyno_title;
    lv_obj_t *obj37;
    lv_obj_t *dyno_counter_caption;
    lv_obj_t *dyno_counter;
    lv_obj_t *obj38;
    lv_obj_t *dyno_state_caption;
    lv_obj_t *dyno_state;
    lv_obj_t *dyno_no_vcu;
    lv_obj_t *debug_title;
    lv_obj_t *debug_vcu;
    lv_obj_t *debug_link_ok;
    lv_obj_t *debug_link_lost;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *obj42;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
    lv_obj_t *obj45;
    lv_obj_t *obj46;
    lv_obj_t *obj47;
    lv_obj_t *obj48;
    lv_obj_t *obj49;
    lv_obj_t *obj50;
    lv_obj_t *obj51;
    lv_obj_t *obj52;
    lv_obj_t *obj53;
    lv_obj_t *obj54;
    lv_obj_t *obj55;
    lv_obj_t *obj56;
    lv_obj_t *obj57;
    lv_obj_t *obj58;
    lv_obj_t *obj59;
    lv_obj_t *obj60;
    lv_obj_t *obj61;
    lv_obj_t *obj62;
    lv_obj_t *obj63;
    lv_obj_t *obj64;
    lv_obj_t *obj65;
    lv_obj_t *obj66;
    lv_obj_t *obj67;
    lv_obj_t *obj68;
    lv_obj_t *obj69;
    lv_obj_t *obj70;
    lv_obj_t *obj71;
    lv_obj_t *obj72;
    lv_obj_t *obj73;
    lv_obj_t *obj74;
    lv_obj_t *obj75;
    lv_obj_t *obj76;
    lv_obj_t *obj77;
    lv_obj_t *obj78;
    lv_obj_t *obj79;
    lv_obj_t *obj80;
    lv_obj_t *obj81;
    lv_obj_t *obj82;
    lv_obj_t *sponsors_title;
    lv_obj_t *obj83;
    lv_obj_t *sponsors_logo_uos;
    lv_obj_t *sponsors_dot_0;
    lv_obj_t *sponsors_dot_on_0;
    lv_obj_t *sponsors_logo_sfs;
    lv_obj_t *sponsors_dot_1;
    lv_obj_t *sponsors_dot_on_1;
    lv_obj_t *sponsors_logo_vector;
    lv_obj_t *sponsors_dot_2;
    lv_obj_t *sponsors_dot_on_2;
    lv_obj_t *sponsors_logo_rfpro;
    lv_obj_t *sponsors_dot_3;
    lv_obj_t *sponsors_dot_on_3;
    lv_obj_t *sponsors_logo_about_energy;
    lv_obj_t *sponsors_dot_4;
    lv_obj_t *sponsors_dot_on_4;
} objects_t;

extern objects_t objects;

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_skidpad();
void delete_screen_skidpad();
void tick_screen_skidpad();

void create_screen_accel();
void delete_screen_accel();
void tick_screen_accel();

void create_screen_dyno();
void delete_screen_dyno();
void tick_screen_dyno();

void create_screen_debug();
void delete_screen_debug();
void tick_screen_debug();

void create_screen_sponsors();
void delete_screen_sponsors();
void tick_screen_sponsors();

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Color themes

enum Themes {
    THEME_ID_DASH_WHITE_BG,
    THEME_ID_DASH_BLACK_BG,
};
enum Colors {
    COLOR_ID_BG,
    COLOR_ID_TEXT,
    COLOR_ID_OK,
    COLOR_ID_WARN,
    COLOR_ID_CRIT,
    COLOR_ID_ON_FILL,
    COLOR_ID_ON_CRIT,
    COLOR_ID_MSG_BG,
    COLOR_ID_BAR_TRACK,
    COLOR_ID_DYNO_BG,
    COLOR_ID_SOC_TRACK,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[2][11];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/