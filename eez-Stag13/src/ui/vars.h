#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LAP_NUMBER = 0,
    FLOW_GLOBAL_VARIABLE_SOC_WARN = 1,
    FLOW_GLOBAL_VARIABLE_SOC_CRIT = 2,
    FLOW_GLOBAL_VARIABLE_BATT_WARN = 3,
    FLOW_GLOBAL_VARIABLE_BATT_CRIT = 4,
    FLOW_GLOBAL_VARIABLE_MOTOR_WARN = 5,
    FLOW_GLOBAL_VARIABLE_MOTOR_CRIT = 6,
    FLOW_GLOBAL_VARIABLE_INV_WARN = 7,
    FLOW_GLOBAL_VARIABLE_INV_CRIT = 8,
    FLOW_GLOBAL_VARIABLE_DRIVER_MSG = 9,
    FLOW_GLOBAL_VARIABLE_SLIP_WARN = 10,
    FLOW_GLOBAL_VARIABLE_TOTAL_LAPS = 11,
    FLOW_GLOBAL_VARIABLE_LAP_LENGTH = 12,
    FLOW_GLOBAL_VARIABLE_TC_ON = 13,
    FLOW_GLOBAL_VARIABLE_SPLASH_MS = 14
};

// Native global variables

extern int32_t get_var_vcu_rolling_counter();
extern void set_var_vcu_rolling_counter(int32_t value);
extern double get_var_bms_pack_inst_voltage();
extern void set_var_bms_pack_inst_voltage(double value);
extern double get_var_wheel_fl_speed();
extern void set_var_wheel_fl_speed(double value);
extern double get_var_bms_pack_current();
extern void set_var_bms_pack_current(double value);
extern double get_var_pdm_input_10_voltage();
extern void set_var_pdm_input_10_voltage(double value);
extern double get_var_wheel_fr_speed();
extern void set_var_wheel_fr_speed(double value);
extern double get_var_wheel_rl_speed();
extern void set_var_wheel_rl_speed(double value);
extern double get_var_wheel_rr_speed();
extern void set_var_wheel_rr_speed(double value);
extern const char *get_var_vcu_ctrl_state();
extern void set_var_vcu_ctrl_state(const char *value);
extern const char *get_var_pm100_vsm_state();
extern void set_var_pm100_vsm_state(const char *value);
extern double get_var_vcu_sagl();
extern void set_var_vcu_sagl(double value);
extern double get_var_vcu_apps();
extern void set_var_vcu_apps(double value);
extern double get_var_vcu_bps();
extern void set_var_vcu_bps(double value);
extern double get_var_pm100_module_a();
extern void set_var_pm100_module_a(double value);
extern double get_var_pm100_module_b();
extern void set_var_pm100_module_b(double value);
extern double get_var_pm100_module_c();
extern void set_var_pm100_module_c(double value);
extern double get_var_pm100_gate_driver_board();
extern void set_var_pm100_gate_driver_board(double value);
extern double get_var_pm100_motor_temperature();
extern void set_var_pm100_motor_temperature(double value);
extern int32_t get_var_bms_high_temperature();
extern void set_var_bms_high_temperature(int32_t value);
extern int32_t get_var_bms_average_temperature();
extern void set_var_bms_average_temperature(int32_t value);
extern const char *get_var_vcu_current_mode();
extern void set_var_vcu_current_mode(const char *value);
extern const char *get_var_vcu_requested_mode();
extern void set_var_vcu_requested_mode(const char *value);
extern double get_var_lvbox_pwr();
extern void set_var_lvbox_pwr(double value);
extern bool get_var_inverter();
extern void set_var_inverter(bool value);
extern bool get_var_brakelight();
extern void set_var_brakelight(bool value);
extern bool get_var_pump();
extern void set_var_pump(bool value);
extern bool get_var_fan();
extern void set_var_fan(bool value);
extern double get_var_pdm_battery_voltage();
extern void set_var_pdm_battery_voltage(double value);
extern const char *get_var_uptime_str();
extern void set_var_uptime_str(const char *value);
extern int32_t get_var_bms_pack_soc();
extern void set_var_bms_pack_soc(int32_t value);
extern const char *get_var_vcu_lc_state();
extern void set_var_vcu_lc_state(const char *value);
extern const char *get_var_vcu_lc_fault();
extern void set_var_vcu_lc_fault(const char *value);
extern bool get_var_vcu_lc_shadow_mode();
extern void set_var_vcu_lc_shadow_mode(bool value);
extern bool get_var_vcu_lc_stationary();
extern void set_var_vcu_lc_stationary(bool value);
extern int32_t get_var_vcu_lc_arm_progress();
extern void set_var_vcu_lc_arm_progress(int32_t value);
extern int32_t get_var_vcu_ctrl_error();
extern void set_var_vcu_ctrl_error(int32_t value);
extern int32_t get_var_vcu_scs_error();
extern void set_var_vcu_scs_error(int32_t value);
extern int32_t get_var_vcu_pm100_error();
extern void set_var_vcu_pm100_error(int32_t value);
extern int32_t get_var_vcu_rtcan1_error();
extern void set_var_vcu_rtcan1_error(int32_t value);
extern int32_t get_var_vcu_rtcan2_error();
extern void set_var_vcu_rtcan2_error(int32_t value);
extern int32_t get_var_vcu_canbc_error();
extern void set_var_vcu_canbc_error(int32_t value);
extern int32_t get_var_vcu_apps1_raw();
extern void set_var_vcu_apps1_raw(int32_t value);
extern int32_t get_var_vcu_apps2_raw();
extern void set_var_vcu_apps2_raw(int32_t value);
extern int32_t get_var_vcu_bps_raw();
extern void set_var_vcu_bps_raw(int32_t value);
extern int32_t get_var_vcu_max_temp();
extern void set_var_vcu_max_temp(int32_t value);
extern bool get_var_tap_estops();
extern void set_var_tap_estops(bool value);
extern bool get_var_imd_fault();
extern void set_var_imd_fault(bool value);
extern bool get_var_ams_fault();
extern void set_var_ams_fault(bool value);
extern bool get_var_ts_detected();
extern void set_var_ts_detected(bool value);
extern bool get_var_tap_latching();
extern void set_var_tap_latching(bool value);
extern bool get_var_tap_hvd();
extern void set_var_tap_hvd(bool value);
extern bool get_var_tap_bots();
extern void set_var_tap_bots(bool value);
extern bool get_var_tap_estop();
extern void set_var_tap_estop(bool value);
extern bool get_var_tap_sdc_inertia();
extern void set_var_tap_sdc_inertia(bool value);
extern bool get_var_bspd_status();
extern void set_var_bspd_status(bool value);
extern const char *get_var_can_s_status();
extern void set_var_can_s_status(const char *value);
extern const char *get_var_can_t_status();
extern void set_var_can_t_status(const char *value);
extern int32_t get_var_can_rx_dropped();
extern void set_var_can_rx_dropped(int32_t value);
extern bool get_var_vcu_link_ok();
extern void set_var_vcu_link_ok(bool value);
extern int32_t get_var_uptime_s();
extern void set_var_uptime_s(int32_t value);
extern int32_t get_var_inv_level();
extern void set_var_inv_level(int32_t value);
extern int32_t get_var_motor_level();
extern void set_var_motor_level(int32_t value);
extern int32_t get_var_batt_level();
extern void set_var_batt_level(int32_t value);
extern int32_t get_var_soc_level();
extern void set_var_soc_level(int32_t value);
extern int32_t get_var_soc_target();
extern void set_var_soc_target(int32_t value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/