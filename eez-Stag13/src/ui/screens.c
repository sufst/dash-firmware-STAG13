#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

static const char *screen_names[] = { "Main", "Skidpad", "Accel", "Dyno", "Debug", "Sponsors" };
static const char *object_names[] = { "main", "skidpad", "accel", "dyno", "debug", "sponsors", "lvbox_pwr", "vcu_state", "inv_state", "obj0", "pdm_11", "apps", "bps", "obj1", "lap_number", "obj2", "inverter_on", "inverter_off", "pumps_on", "pumps_off", "fans_on", "fans_off", "tc_on", "tc_off", "battery_ok", "battery_warn", "battery_crit", "motor_ok", "motor_warn", "motor_cit", "inverter_ok", "inverter_warn", "inverter_cit", "obj3", "inverter_temp", "inverter_temp_4", "inverter_temp_5", "motor_temp", "inverter_temp_6", "battery_temp", "obj4", "obj5", "obj6", "obj7", "obj8", "obj9", "obj10", "obj11", "soc_percent", "soc_percent_warn", "soc_percent_crit", "mode", "inverter_switch_label", "pumps_switch_label", "fans_switch_label", "tc_switch_label", "obj12", "obj13", "obj14", "startup_instructions", "soc_target_text", "soc_target_text_neg", "soc", "soc__", "skidpad_lvbox_pwr", "skidpad_vcu_state", "skidpad_inv_state", "obj15", "skidpad_pdm_11", "skidpad_apps", "skidpad_bps", "obj16", "skidpad_lap_number", "obj17", "skidpad_inverter_on", "skidpad_inverter_off", "skidpad_pumps_on", "skidpad_pumps_off", "skidpad_fans_on", "skidpad_fans_off", "skidpad_tc_on", "skidpad_tc_off", "skidpad_battery_ok", "skidpad_battery_warn", "skidpad_battery_crit", "skidpad_motor_ok", "skidpad_motor_warn", "skidpad_motor_cit", "skidpad_inverter_ok", "skidpad_inverter_warn", "skidpad_inverter_cit", "obj18", "skidpad_inverter_temp", "skidpad_inverter_temp_4", "skidpad_inverter_temp_5", "skidpad_motor_temp", "skidpad_inverter_temp_6", "skidpad_battery_temp", "obj19", "obj20", "obj21", "obj22", "obj23", "obj24", "obj25", "obj26", "skidpad_soc_percent", "skidpad_soc_percent_warn", "skidpad_soc_percent_crit", "skidpad_mode", "skidpad_inverter_switch_label", "skidpad_pumps_switch_label", "skidpad_fans_switch_label", "skidpad_tc_switch_label", "obj27", "obj28", "obj29", "skidpad_startup_instructions", "skidpad_soc", "accel_inv_state", "obj30", "accel_pdm_11", "accel_apps", "accel_bps", "obj31", "obj32", "accel_inverter_on", "accel_inverter_off", "accel_pumps_on", "accel_pumps_off", "accel_fans_on", "accel_fans_off", "accel_tc_on", "accel_tc_off", "accel_battery_ok", "accel_battery_warn", "accel_battery_crit", "accel_motor_ok", "accel_motor_warn", "accel_motor_cit", "accel_inverter_ok", "accel_inverter_warn", "accel_inverter_cit", "obj33", "accel_inverter_temp", "accel_inverter_temp_4", "accel_inverter_temp_5", "accel_motor_temp", "accel_inverter_temp_6", "accel_battery_temp", "obj34", "obj35", "obj36", "obj37", "obj38", "obj39", "obj40", "accel_soc_percent", "accel_soc_percent_warn", "accel_soc_percent_crit", "accel_mode", "accel_inverter_switch_label", "accel_pumps_switch_label", "accel_fans_switch_label", "accel_tc_switch_label", "obj41", "obj42", "obj43", "accel_launch_header", "obj44", "accel_startup_instructions", "accel_lc_status", "accel_lc_status_go", "accel_lc_status_fault", "accel_lc_hint", "accel_lc_arm_bar", "accel_lc_fault_reason", "accel_lc_shadow", "accel_slip_warn", "accel_speed", "accel_slip", "accel_vcu_state", "accel_lvbox_pwr", "dyno_title", "obj45", "dyno_counter_caption", "dyno_counter", "obj46", "dyno_state_caption", "dyno_state", "dyno_no_vcu", "debug_title", "debug_vcu", "debug_link_ok", "debug_link_lost", "obj47", "obj48", "obj49", "obj50", "obj51", "obj52", "obj53", "obj54", "obj55", "obj56", "obj57", "obj58", "obj59", "obj60", "obj61", "obj62", "obj63", "obj64", "obj65", "obj66", "obj67", "obj68", "obj69", "obj70", "obj71", "obj72", "obj73", "obj74", "obj75", "obj76", "obj77", "obj78", "obj79", "obj80", "obj81", "obj82", "obj83", "obj84", "obj85", "obj86", "obj87", "obj88", "obj89", "obj90", "sponsors_title", "obj91", "sponsors_logo_uos", "sponsors_dot_0", "sponsors_dot_on_0", "sponsors_logo_sfs", "sponsors_dot_1", "sponsors_dot_on_1", "sponsors_logo_vector", "sponsors_dot_2", "sponsors_dot_on_2", "sponsors_logo_rfpro", "sponsors_dot_3", "sponsors_dot_on_3", "sponsors_logo_about_energy", "sponsors_dot_4", "sponsors_dot_on_4" };

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 4, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_skidpad_obj15(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 4, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_accel_obj30(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 2, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

//
// Screens
//

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // lvbox_pwr
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lvbox_pwr = obj;
            lv_obj_set_pos(obj, 616, 350);
            lv_obj_set_size(obj, 180, 34);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // vcu_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vcu_state = obj;
            lv_obj_set_pos(obj, 616, 299);
            lv_obj_set_size(obj, 180, 48);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inv_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inv_state = obj;
            lv_obj_set_pos(obj, 443, 336);
            lv_obj_set_size(obj, 165, 48);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 17, 73);
            lv_obj_set_size(obj, 38, 36);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
            lv_obj_set_style_pad_top(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // pdm_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_11 = obj;
            lv_obj_set_pos(obj, 443, 300);
            lv_obj_set_size(obj, 165, 34);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // apps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.apps = obj;
            lv_obj_set_pos(obj, 55, 71);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 251, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xabd0ee), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // bps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.bps = obj;
            lv_obj_set_pos(obj, 1, 72);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xbcd8ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 251, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_stag);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            // lap_number
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lap_number = obj;
            lv_obj_set_pos(obj, 625, 398);
            lv_obj_set_size(obj, 167, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 609, 298);
            lv_obj_set_size(obj, 3, 183);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // inverter_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.inverter_on = obj;
            lv_obj_set_pos(obj, 0, 387);
            lv_obj_set_size(obj, 150, 93);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // inverter_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.inverter_off = obj;
            lv_obj_set_pos(obj, 0, 386);
            lv_obj_set_size(obj, 150, 93);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pumps_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pumps_on = obj;
            lv_obj_set_pos(obj, 153, 385);
            lv_obj_set_size(obj, 150, 97);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // pumps_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.pumps_off = obj;
            lv_obj_set_pos(obj, 153, 387);
            lv_obj_set_size(obj, 150, 97);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fans_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fans_on = obj;
            lv_obj_set_pos(obj, 306, 386);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fans_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fans_off = obj;
            lv_obj_set_pos(obj, 306, 387);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // tc_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.tc_on = obj;
            lv_obj_set_pos(obj, 459, 386);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // tc_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.tc_off = obj;
            lv_obj_set_pos(obj, 459, 387);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // battery_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.battery_ok = obj;
            lv_obj_set_pos(obj, 0, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // battery_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.battery_warn = obj;
            lv_obj_set_pos(obj, 0, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // battery_crit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.battery_crit = obj;
            lv_obj_set_pos(obj, 1, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // motor_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.motor_ok = obj;
            lv_obj_set_pos(obj, 0, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // motor_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.motor_warn = obj;
            lv_obj_set_pos(obj, 0, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // motor_cit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.motor_cit = obj;
            lv_obj_set_pos(obj, 1, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // inverter_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.inverter_ok = obj;
            lv_obj_set_pos(obj, -1, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // inverter_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.inverter_warn = obj;
            lv_obj_set_pos(obj, 0, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // inverter_cit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.inverter_cit = obj;
            lv_obj_set_pos(obj, -1, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 0, 121);
            lv_obj_set_size(obj, 440, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // inverter_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp = obj;
            lv_obj_set_pos(obj, 266, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_temp_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_4 = obj;
            lv_obj_set_pos(obj, 18, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // inverter_temp_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_5 = obj;
            lv_obj_set_pos(obj, 17, 224);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Motor");
        }
        {
            // motor_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.motor_temp = obj;
            lv_obj_set_pos(obj, 266, 225);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_temp_6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_6 = obj;
            lv_obj_set_pos(obj, 17, 311);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Battery");
        }
        {
            // battery_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery_temp = obj;
            lv_obj_set_pos(obj, 266, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 611, 385);
            lv_obj_set_size(obj, 192, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 0, 207);
            lv_obj_set_size(obj, 437, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 437, 0);
            lv_obj_set_size(obj, 3, 389);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 0, 385);
            lv_obj_set_size(obj, 612, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 0, 296);
            lv_obj_set_size(obj, 437, 3);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj9 = obj;
            lv_obj_set_pos(obj, 438, 295);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj10 = obj;
            lv_obj_set_pos(obj, 439, 121);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj11 = obj;
            lv_obj_set_pos(obj, 438, 207);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // soc_percent
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc_percent = obj;
            lv_obj_set_pos(obj, 592, 131);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // soc_percent_warn
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc_percent_warn = obj;
            lv_obj_set_pos(obj, 592, 131);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // soc_percent_crit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc_percent_crit = obj;
            lv_obj_set_pos(obj, 592, 131);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // mode
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mode = obj;
            lv_obj_set_pos(obj, 85, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_switch_label = obj;
            lv_obj_set_pos(obj, 0, 411);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // pumps_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pumps_switch_label = obj;
            lv_obj_set_pos(obj, 153, 413);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Pumps");
        }
        {
            // fans_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fans_switch_label = obj;
            lv_obj_set_pos(obj, 306, 414);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fans");
        }
        {
            // tc_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tc_switch_label = obj;
            lv_obj_set_pos(obj, 459, 414);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "TC");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj12 = obj;
            lv_obj_set_pos(obj, 150, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj13 = obj;
            lv_obj_set_pos(obj, 303, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj14 = obj;
            lv_obj_set_pos(obj, 456, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // startup_instructions
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.startup_instructions = obj;
            lv_obj_set_pos(obj, 462, 20);
            lv_obj_set_size(obj, 316, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // soc_target_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc_target_text = obj;
            lv_obj_set_pos(obj, 592, 218);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // soc_target_text_neg
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc_target_text_neg = obj;
            lv_obj_set_pos(obj, 592, 218);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_CLIP);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // soc
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc = obj;
            lv_obj_set_pos(obj, 471, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "SOC");
        }
        {
            // soc+-
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.soc__ = obj;
            lv_obj_set_pos(obj, 475, 222);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "+/-");
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_MAIN - 1);
    
    tick_screen_main();
}

void delete_screen_main() {
    lv_obj_del(objects.main);
    objects.main = 0;
    objects.lvbox_pwr = 0;
    objects.vcu_state = 0;
    objects.inv_state = 0;
    objects.obj0 = 0;
    objects.pdm_11 = 0;
    objects.apps = 0;
    objects.bps = 0;
    objects.obj1 = 0;
    objects.lap_number = 0;
    objects.obj2 = 0;
    objects.inverter_on = 0;
    objects.inverter_off = 0;
    objects.pumps_on = 0;
    objects.pumps_off = 0;
    objects.fans_on = 0;
    objects.fans_off = 0;
    objects.tc_on = 0;
    objects.tc_off = 0;
    objects.battery_ok = 0;
    objects.battery_warn = 0;
    objects.battery_crit = 0;
    objects.motor_ok = 0;
    objects.motor_warn = 0;
    objects.motor_cit = 0;
    objects.inverter_ok = 0;
    objects.inverter_warn = 0;
    objects.inverter_cit = 0;
    objects.obj3 = 0;
    objects.inverter_temp = 0;
    objects.inverter_temp_4 = 0;
    objects.inverter_temp_5 = 0;
    objects.motor_temp = 0;
    objects.inverter_temp_6 = 0;
    objects.battery_temp = 0;
    objects.obj4 = 0;
    objects.obj5 = 0;
    objects.obj6 = 0;
    objects.obj7 = 0;
    objects.obj8 = 0;
    objects.obj9 = 0;
    objects.obj10 = 0;
    objects.obj11 = 0;
    objects.soc_percent = 0;
    objects.soc_percent_warn = 0;
    objects.soc_percent_crit = 0;
    objects.mode = 0;
    objects.inverter_switch_label = 0;
    objects.pumps_switch_label = 0;
    objects.fans_switch_label = 0;
    objects.tc_switch_label = 0;
    objects.obj12 = 0;
    objects.obj13 = 0;
    objects.obj14 = 0;
    objects.startup_instructions = 0;
    objects.soc_target_text = 0;
    objects.soc_target_text_neg = 0;
    objects.soc = 0;
    objects.soc__ = 0;
    deletePageFlowState(0);
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.lvbox_pwr);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.lvbox_pwr;
            lv_label_set_text(objects.lvbox_pwr, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.vcu_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vcu_state;
            lv_label_set_text(objects.vcu_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inv_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inv_state;
            lv_label_set_text(objects.inv_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj0);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            lv_arc_set_value(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_11;
            lv_label_set_text(objects.pdm_11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 6, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.apps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.apps;
            lv_bar_set_value(objects.apps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 7, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.bps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.bps;
            lv_bar_set_value(objects.bps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.lap_number);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.lap_number;
            lv_label_set_text(objects.lap_number, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 12, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.inverter_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.inverter_off;
            if (new_val) {
                lv_obj_add_flag(objects.inverter_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.inverter_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 14, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.pumps_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.pumps_off;
            if (new_val) {
                lv_obj_add_flag(objects.pumps_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.pumps_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.fans_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.fans_off;
            if (new_val) {
                lv_obj_add_flag(objects.fans_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.fans_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.tc_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.tc_off;
            if (new_val) {
                lv_obj_add_flag(objects.tc_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.tc_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.battery_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.battery_warn;
            if (new_val) {
                lv_obj_add_flag(objects.battery_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.battery_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.battery_crit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.battery_crit;
            if (new_val) {
                lv_obj_add_flag(objects.battery_crit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.battery_crit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.motor_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.motor_warn;
            if (new_val) {
                lv_obj_add_flag(objects.motor_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.motor_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.motor_cit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.motor_cit;
            if (new_val) {
                lv_obj_add_flag(objects.motor_cit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.motor_cit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.inverter_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.inverter_warn;
            if (new_val) {
                lv_obj_add_flag(objects.inverter_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.inverter_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.inverter_cit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.inverter_cit;
            if (new_val) {
                lv_obj_add_flag(objects.inverter_cit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.inverter_cit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inverter_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inverter_temp;
            lv_label_set_text(objects.inverter_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 32, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.motor_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.motor_temp;
            lv_label_set_text(objects.motor_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 34, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.battery_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.battery_temp;
            lv_label_set_text(objects.battery_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 43, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.soc_percent);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.soc_percent;
            lv_label_set_text(objects.soc_percent, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.soc_percent, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.soc_percent;
            if (new_val) {
                lv_obj_add_flag(objects.soc_percent, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.soc_percent, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 44, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.soc_percent_warn);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.soc_percent_warn;
            lv_label_set_text(objects.soc_percent_warn, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 44, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.soc_percent_warn;
            if (new_val) {
                lv_obj_add_flag(objects.soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 45, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.soc_percent_crit);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.soc_percent_crit;
            lv_label_set_text(objects.soc_percent_crit, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.soc_percent_crit;
            if (new_val) {
                lv_obj_add_flag(objects.soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 46, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.mode);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.mode;
            lv_label_set_text(objects.mode, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 54, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.startup_instructions);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.startup_instructions;
            lv_label_set_text(objects.startup_instructions, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 54, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.startup_instructions, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.startup_instructions;
            if (new_val) {
                lv_obj_add_flag(objects.startup_instructions, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.startup_instructions, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 55, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.soc_target_text);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.soc_target_text;
            lv_label_set_text(objects.soc_target_text, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 55, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.soc_target_text, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.soc_target_text;
            if (new_val) {
                lv_obj_add_flag(objects.soc_target_text, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.soc_target_text, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 56, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.soc_target_text_neg);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.soc_target_text_neg;
            lv_label_set_text(objects.soc_target_text_neg, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 56, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.soc_target_text_neg, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.soc_target_text_neg;
            if (new_val) {
                lv_obj_add_flag(objects.soc_target_text_neg, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.soc_target_text_neg, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 58, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.soc__, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.soc__;
            if (new_val) {
                lv_obj_add_flag(objects.soc__, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.soc__, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_skidpad() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.skidpad = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // skidpad_lvbox_pwr
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_lvbox_pwr = obj;
            lv_obj_set_pos(obj, 616, 350);
            lv_obj_set_size(obj, 180, 34);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_vcu_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_vcu_state = obj;
            lv_obj_set_pos(obj, 616, 299);
            lv_obj_set_size(obj, 180, 48);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_inv_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_inv_state = obj;
            lv_obj_set_pos(obj, 443, 336);
            lv_obj_set_size(obj, 165, 48);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj15 = obj;
            lv_obj_set_pos(obj, 17, 73);
            lv_obj_set_size(obj, 38, 36);
            lv_obj_add_event_cb(obj, event_handler_cb_skidpad_obj15, LV_EVENT_ALL, flowState);
            lv_obj_set_style_pad_top(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // skidpad_pdm_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_pdm_11 = obj;
            lv_obj_set_pos(obj, 443, 300);
            lv_obj_set_size(obj, 165, 34);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_apps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.skidpad_apps = obj;
            lv_obj_set_pos(obj, 55, 71);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 251, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xabd0ee), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_bps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.skidpad_bps = obj;
            lv_obj_set_pos(obj, 1, 72);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xbcd8ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 251, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.obj16 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_stag);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            // skidpad_lap_number
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_lap_number = obj;
            lv_obj_set_pos(obj, 625, 398);
            lv_obj_set_size(obj, 167, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj17 = obj;
            lv_obj_set_pos(obj, 609, 298);
            lv_obj_set_size(obj, 3, 183);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_inverter_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_inverter_on = obj;
            lv_obj_set_pos(obj, 0, 387);
            lv_obj_set_size(obj, 150, 93);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_inverter_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_inverter_off = obj;
            lv_obj_set_pos(obj, 0, 386);
            lv_obj_set_size(obj, 150, 93);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_pumps_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_pumps_on = obj;
            lv_obj_set_pos(obj, 153, 385);
            lv_obj_set_size(obj, 150, 97);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_pumps_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_pumps_off = obj;
            lv_obj_set_pos(obj, 153, 387);
            lv_obj_set_size(obj, 150, 97);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_fans_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_fans_on = obj;
            lv_obj_set_pos(obj, 306, 386);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_fans_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_fans_off = obj;
            lv_obj_set_pos(obj, 306, 387);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_tc_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_tc_on = obj;
            lv_obj_set_pos(obj, 459, 386);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_tc_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_tc_off = obj;
            lv_obj_set_pos(obj, 459, 387);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_battery_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_battery_ok = obj;
            lv_obj_set_pos(obj, 0, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_battery_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_battery_warn = obj;
            lv_obj_set_pos(obj, 0, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_battery_crit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_battery_crit = obj;
            lv_obj_set_pos(obj, 1, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_motor_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_motor_ok = obj;
            lv_obj_set_pos(obj, 0, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_motor_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_motor_warn = obj;
            lv_obj_set_pos(obj, 0, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_motor_cit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_motor_cit = obj;
            lv_obj_set_pos(obj, 1, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_inverter_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_inverter_ok = obj;
            lv_obj_set_pos(obj, -1, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_inverter_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_inverter_warn = obj;
            lv_obj_set_pos(obj, 0, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_inverter_cit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.skidpad_inverter_cit = obj;
            lv_obj_set_pos(obj, -1, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj18 = obj;
            lv_obj_set_pos(obj, 0, 121);
            lv_obj_set_size(obj, 440, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_inverter_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_inverter_temp = obj;
            lv_obj_set_pos(obj, 266, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_inverter_temp_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_inverter_temp_4 = obj;
            lv_obj_set_pos(obj, 18, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // skidpad_inverter_temp_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_inverter_temp_5 = obj;
            lv_obj_set_pos(obj, 17, 224);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Motor");
        }
        {
            // skidpad_motor_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_motor_temp = obj;
            lv_obj_set_pos(obj, 266, 225);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_inverter_temp_6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_inverter_temp_6 = obj;
            lv_obj_set_pos(obj, 17, 311);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Battery");
        }
        {
            // skidpad_battery_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_battery_temp = obj;
            lv_obj_set_pos(obj, 266, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj19 = obj;
            lv_obj_set_pos(obj, 611, 385);
            lv_obj_set_size(obj, 192, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj20 = obj;
            lv_obj_set_pos(obj, 0, 207);
            lv_obj_set_size(obj, 437, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj21 = obj;
            lv_obj_set_pos(obj, 437, 0);
            lv_obj_set_size(obj, 3, 389);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj22 = obj;
            lv_obj_set_pos(obj, 0, 385);
            lv_obj_set_size(obj, 612, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj23 = obj;
            lv_obj_set_pos(obj, 0, 296);
            lv_obj_set_size(obj, 437, 3);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj24 = obj;
            lv_obj_set_pos(obj, 438, 295);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj25 = obj;
            lv_obj_set_pos(obj, 439, 121);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj26 = obj;
            lv_obj_set_pos(obj, 438, 207);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_soc_percent
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_soc_percent = obj;
            lv_obj_set_pos(obj, 592, 131);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_soc_percent_warn
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_soc_percent_warn = obj;
            lv_obj_set_pos(obj, 592, 131);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_soc_percent_crit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_soc_percent_crit = obj;
            lv_obj_set_pos(obj, 592, 131);
            lv_obj_set_size(obj, 205, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_mode
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_mode = obj;
            lv_obj_set_pos(obj, 85, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Skidpad");
        }
        {
            // skidpad_inverter_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_inverter_switch_label = obj;
            lv_obj_set_pos(obj, 0, 411);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // skidpad_pumps_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_pumps_switch_label = obj;
            lv_obj_set_pos(obj, 153, 413);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Pumps");
        }
        {
            // skidpad_fans_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_fans_switch_label = obj;
            lv_obj_set_pos(obj, 306, 414);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fans");
        }
        {
            // skidpad_tc_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_tc_switch_label = obj;
            lv_obj_set_pos(obj, 459, 414);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "TC");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj27 = obj;
            lv_obj_set_pos(obj, 150, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj28 = obj;
            lv_obj_set_pos(obj, 303, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj29 = obj;
            lv_obj_set_pos(obj, 456, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // skidpad_startup_instructions
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_startup_instructions = obj;
            lv_obj_set_pos(obj, 462, 20);
            lv_obj_set_size(obj, 316, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // skidpad_soc
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.skidpad_soc = obj;
            lv_obj_set_pos(obj, 471, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "SOC");
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_SKIDPAD - 1);
    
    tick_screen_skidpad();
}

void delete_screen_skidpad() {
    lv_obj_del(objects.skidpad);
    objects.skidpad = 0;
    objects.skidpad_lvbox_pwr = 0;
    objects.skidpad_vcu_state = 0;
    objects.skidpad_inv_state = 0;
    objects.obj15 = 0;
    objects.skidpad_pdm_11 = 0;
    objects.skidpad_apps = 0;
    objects.skidpad_bps = 0;
    objects.obj16 = 0;
    objects.skidpad_lap_number = 0;
    objects.obj17 = 0;
    objects.skidpad_inverter_on = 0;
    objects.skidpad_inverter_off = 0;
    objects.skidpad_pumps_on = 0;
    objects.skidpad_pumps_off = 0;
    objects.skidpad_fans_on = 0;
    objects.skidpad_fans_off = 0;
    objects.skidpad_tc_on = 0;
    objects.skidpad_tc_off = 0;
    objects.skidpad_battery_ok = 0;
    objects.skidpad_battery_warn = 0;
    objects.skidpad_battery_crit = 0;
    objects.skidpad_motor_ok = 0;
    objects.skidpad_motor_warn = 0;
    objects.skidpad_motor_cit = 0;
    objects.skidpad_inverter_ok = 0;
    objects.skidpad_inverter_warn = 0;
    objects.skidpad_inverter_cit = 0;
    objects.obj18 = 0;
    objects.skidpad_inverter_temp = 0;
    objects.skidpad_inverter_temp_4 = 0;
    objects.skidpad_inverter_temp_5 = 0;
    objects.skidpad_motor_temp = 0;
    objects.skidpad_inverter_temp_6 = 0;
    objects.skidpad_battery_temp = 0;
    objects.obj19 = 0;
    objects.obj20 = 0;
    objects.obj21 = 0;
    objects.obj22 = 0;
    objects.obj23 = 0;
    objects.obj24 = 0;
    objects.obj25 = 0;
    objects.obj26 = 0;
    objects.skidpad_soc_percent = 0;
    objects.skidpad_soc_percent_warn = 0;
    objects.skidpad_soc_percent_crit = 0;
    objects.skidpad_mode = 0;
    objects.skidpad_inverter_switch_label = 0;
    objects.skidpad_pumps_switch_label = 0;
    objects.skidpad_fans_switch_label = 0;
    objects.skidpad_tc_switch_label = 0;
    objects.obj27 = 0;
    objects.obj28 = 0;
    objects.obj29 = 0;
    objects.skidpad_startup_instructions = 0;
    objects.skidpad_soc = 0;
    deletePageFlowState(1);
}

void tick_screen_skidpad() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_lvbox_pwr);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_lvbox_pwr;
            lv_label_set_text(objects.skidpad_lvbox_pwr, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_vcu_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_vcu_state;
            lv_label_set_text(objects.skidpad_vcu_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_inv_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_inv_state;
            lv_label_set_text(objects.skidpad_inv_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj15);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj15;
            lv_arc_set_value(objects.obj15, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_pdm_11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_pdm_11;
            lv_label_set_text(objects.skidpad_pdm_11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 6, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.skidpad_apps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_apps;
            lv_bar_set_value(objects.skidpad_apps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 7, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.skidpad_bps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_bps;
            lv_bar_set_value(objects.skidpad_bps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_lap_number);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_lap_number;
            lv_label_set_text(objects.skidpad_lap_number, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 12, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_inverter_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_inverter_off;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_inverter_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_inverter_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 14, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_pumps_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_pumps_off;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_pumps_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_pumps_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 16, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_fans_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_fans_off;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_fans_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_fans_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_tc_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_tc_off;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_tc_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_tc_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_battery_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_battery_warn;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_battery_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_battery_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_battery_crit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_battery_crit;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_battery_crit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_battery_crit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_motor_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_motor_warn;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_motor_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_motor_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_motor_cit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_motor_cit;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_motor_cit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_motor_cit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 26, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_inverter_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_inverter_warn;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_inverter_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_inverter_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_inverter_cit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_inverter_cit;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_inverter_cit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_inverter_cit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_inverter_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_inverter_temp;
            lv_label_set_text(objects.skidpad_inverter_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 32, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_motor_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_motor_temp;
            lv_label_set_text(objects.skidpad_motor_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 34, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_battery_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_battery_temp;
            lv_label_set_text(objects.skidpad_battery_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 43, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_soc_percent);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_soc_percent;
            lv_label_set_text(objects.skidpad_soc_percent, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 43, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_soc_percent, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_soc_percent;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_soc_percent, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_soc_percent, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 44, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_soc_percent_warn);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_soc_percent_warn;
            lv_label_set_text(objects.skidpad_soc_percent_warn, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 44, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_soc_percent_warn;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 45, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_soc_percent_crit);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_soc_percent_crit;
            lv_label_set_text(objects.skidpad_soc_percent_crit, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 45, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_soc_percent_crit;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 54, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.skidpad_startup_instructions);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.skidpad_startup_instructions;
            lv_label_set_text(objects.skidpad_startup_instructions, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 54, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.skidpad_startup_instructions, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.skidpad_startup_instructions;
            if (new_val) {
                lv_obj_add_flag(objects.skidpad_startup_instructions, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.skidpad_startup_instructions, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_accel() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.accel = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // accel_inv_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_inv_state = obj;
            lv_obj_set_pos(obj, 443, 336);
            lv_obj_set_size(obj, 165, 48);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj30 = obj;
            lv_obj_set_pos(obj, 17, 73);
            lv_obj_set_size(obj, 38, 36);
            lv_obj_add_event_cb(obj, event_handler_cb_accel_obj30, LV_EVENT_ALL, flowState);
            lv_obj_set_style_pad_top(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // accel_pdm_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_pdm_11 = obj;
            lv_obj_set_pos(obj, 443, 300);
            lv_obj_set_size(obj, 165, 34);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_apps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.accel_apps = obj;
            lv_obj_set_pos(obj, 55, 71);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 251, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xabd0ee), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_bps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.accel_bps = obj;
            lv_obj_set_pos(obj, 1, 72);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xbcd8ee), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 251, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.obj31 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_stag);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj32 = obj;
            lv_obj_set_pos(obj, 609, 298);
            lv_obj_set_size(obj, 3, 183);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_inverter_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_inverter_on = obj;
            lv_obj_set_pos(obj, 0, 387);
            lv_obj_set_size(obj, 150, 93);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_inverter_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_inverter_off = obj;
            lv_obj_set_pos(obj, 0, 386);
            lv_obj_set_size(obj, 150, 93);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_pumps_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_pumps_on = obj;
            lv_obj_set_pos(obj, 153, 385);
            lv_obj_set_size(obj, 150, 97);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_pumps_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_pumps_off = obj;
            lv_obj_set_pos(obj, 153, 387);
            lv_obj_set_size(obj, 150, 97);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_fans_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_fans_on = obj;
            lv_obj_set_pos(obj, 306, 386);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_fans_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_fans_off = obj;
            lv_obj_set_pos(obj, 306, 387);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_tc_on
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_tc_on = obj;
            lv_obj_set_pos(obj, 459, 386);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_tc_off
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_tc_off = obj;
            lv_obj_set_pos(obj, 459, 387);
            lv_obj_set_size(obj, 150, 99);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_battery_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_battery_ok = obj;
            lv_obj_set_pos(obj, 0, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_battery_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_battery_warn = obj;
            lv_obj_set_pos(obj, 0, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_battery_crit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_battery_crit = obj;
            lv_obj_set_pos(obj, 1, 299);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_motor_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_motor_ok = obj;
            lv_obj_set_pos(obj, 0, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_motor_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_motor_warn = obj;
            lv_obj_set_pos(obj, 0, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_motor_cit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_motor_cit = obj;
            lv_obj_set_pos(obj, 1, 210);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_inverter_ok
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_inverter_ok = obj;
            lv_obj_set_pos(obj, -1, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_inverter_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_inverter_warn = obj;
            lv_obj_set_pos(obj, 0, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_inverter_cit
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_inverter_cit = obj;
            lv_obj_set_pos(obj, -1, 122);
            lv_obj_set_size(obj, 439, 86);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj33 = obj;
            lv_obj_set_pos(obj, 0, 121);
            lv_obj_set_size(obj, 440, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_inverter_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_inverter_temp = obj;
            lv_obj_set_pos(obj, 266, 135);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_inverter_temp_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_inverter_temp_4 = obj;
            lv_obj_set_pos(obj, 18, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // accel_inverter_temp_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_inverter_temp_5 = obj;
            lv_obj_set_pos(obj, 17, 224);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Motor");
        }
        {
            // accel_motor_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_motor_temp = obj;
            lv_obj_set_pos(obj, 266, 225);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_inverter_temp_6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_inverter_temp_6 = obj;
            lv_obj_set_pos(obj, 17, 311);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Battery");
        }
        {
            // accel_battery_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_battery_temp = obj;
            lv_obj_set_pos(obj, 266, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj34 = obj;
            lv_obj_set_pos(obj, 611, 385);
            lv_obj_set_size(obj, 192, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj35 = obj;
            lv_obj_set_pos(obj, 0, 207);
            lv_obj_set_size(obj, 437, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj36 = obj;
            lv_obj_set_pos(obj, 437, 0);
            lv_obj_set_size(obj, 3, 389);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj37 = obj;
            lv_obj_set_pos(obj, 266, -1);
            lv_obj_set_size(obj, 3, 122);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj38 = obj;
            lv_obj_set_pos(obj, 0, 385);
            lv_obj_set_size(obj, 612, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj39 = obj;
            lv_obj_set_pos(obj, 0, 296);
            lv_obj_set_size(obj, 437, 3);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj40 = obj;
            lv_obj_set_pos(obj, 438, 295);
            lv_obj_set_size(obj, 362, 3);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_soc_percent
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_soc_percent = obj;
            lv_obj_set_pos(obj, 270, 40);
            lv_obj_set_size(obj, 166, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_soc_percent_warn
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_soc_percent_warn = obj;
            lv_obj_set_pos(obj, 270, 40);
            lv_obj_set_size(obj, 166, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_soc_percent_crit
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_soc_percent_crit = obj;
            lv_obj_set_pos(obj, 270, 40);
            lv_obj_set_size(obj, 166, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_mode
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_mode = obj;
            lv_obj_set_pos(obj, 85, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Accel");
        }
        {
            // accel_inverter_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_inverter_switch_label = obj;
            lv_obj_set_pos(obj, 0, 411);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // accel_pumps_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_pumps_switch_label = obj;
            lv_obj_set_pos(obj, 153, 413);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Pumps");
        }
        {
            // accel_fans_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_fans_switch_label = obj;
            lv_obj_set_pos(obj, 306, 414);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fans");
        }
        {
            // accel_tc_switch_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_tc_switch_label = obj;
            lv_obj_set_pos(obj, 459, 414);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "TC");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj41 = obj;
            lv_obj_set_pos(obj, 150, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj42 = obj;
            lv_obj_set_pos(obj, 303, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj43 = obj;
            lv_obj_set_pos(obj, 456, 388);
            lv_obj_set_size(obj, 3, 92);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_launch_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_launch_header = obj;
            lv_obj_set_pos(obj, 480, 4);
            lv_obj_set_size(obj, 225, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Launch");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj44 = obj;
            lv_obj_set_pos(obj, 437, 72);
            lv_obj_set_size(obj, 363, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_startup_instructions
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_startup_instructions = obj;
            lv_obj_set_pos(obj, 452, 85);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_lc_status
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lc_status = obj;
            lv_obj_set_pos(obj, 452, 90);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_lc_status_go
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lc_status_go = obj;
            lv_obj_set_pos(obj, 452, 85);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_lc_status_fault
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lc_status_fault = obj;
            lv_obj_set_pos(obj, 452, 85);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "FAULT");
        }
        {
            // accel_lc_hint
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lc_hint = obj;
            lv_obj_set_pos(obj, 452, 160);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_lc_arm_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.accel_lc_arm_bar = obj;
            lv_obj_set_pos(obj, 467, 235);
            lv_obj_set_size(obj, 252, 24);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 3, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // accel_lc_fault_reason
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lc_fault_reason = obj;
            lv_obj_set_pos(obj, 452, 235);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_lc_shadow
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lc_shadow = obj;
            lv_obj_set_pos(obj, 452, 266);
            lv_obj_set_size(obj, 282, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "SHADOW MODE");
        }
        {
            // accel_slip_warn
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.accel_slip_warn = obj;
            lv_obj_set_pos(obj, 612, 436);
            lv_obj_set_size(obj, 188, 44);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // accel_speed
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_speed = obj;
            lv_obj_set_pos(obj, 612, 393);
            lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_slip
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_slip = obj;
            lv_obj_set_pos(obj, 612, 440);
            lv_obj_set_size(obj, 188, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_vcu_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_vcu_state = obj;
            lv_obj_set_pos(obj, 616, 299);
            lv_obj_set_size(obj, 180, 48);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // accel_lvbox_pwr
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.accel_lvbox_pwr = obj;
            lv_obj_set_pos(obj, 616, 350);
            lv_obj_set_size(obj, 180, 34);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_ACCEL - 1);
    
    tick_screen_accel();
}

void delete_screen_accel() {
    lv_obj_del(objects.accel);
    objects.accel = 0;
    objects.accel_inv_state = 0;
    objects.obj30 = 0;
    objects.accel_pdm_11 = 0;
    objects.accel_apps = 0;
    objects.accel_bps = 0;
    objects.obj31 = 0;
    objects.obj32 = 0;
    objects.accel_inverter_on = 0;
    objects.accel_inverter_off = 0;
    objects.accel_pumps_on = 0;
    objects.accel_pumps_off = 0;
    objects.accel_fans_on = 0;
    objects.accel_fans_off = 0;
    objects.accel_tc_on = 0;
    objects.accel_tc_off = 0;
    objects.accel_battery_ok = 0;
    objects.accel_battery_warn = 0;
    objects.accel_battery_crit = 0;
    objects.accel_motor_ok = 0;
    objects.accel_motor_warn = 0;
    objects.accel_motor_cit = 0;
    objects.accel_inverter_ok = 0;
    objects.accel_inverter_warn = 0;
    objects.accel_inverter_cit = 0;
    objects.obj33 = 0;
    objects.accel_inverter_temp = 0;
    objects.accel_inverter_temp_4 = 0;
    objects.accel_inverter_temp_5 = 0;
    objects.accel_motor_temp = 0;
    objects.accel_inverter_temp_6 = 0;
    objects.accel_battery_temp = 0;
    objects.obj34 = 0;
    objects.obj35 = 0;
    objects.obj36 = 0;
    objects.obj37 = 0;
    objects.obj38 = 0;
    objects.obj39 = 0;
    objects.obj40 = 0;
    objects.accel_soc_percent = 0;
    objects.accel_soc_percent_warn = 0;
    objects.accel_soc_percent_crit = 0;
    objects.accel_mode = 0;
    objects.accel_inverter_switch_label = 0;
    objects.accel_pumps_switch_label = 0;
    objects.accel_fans_switch_label = 0;
    objects.accel_tc_switch_label = 0;
    objects.obj41 = 0;
    objects.obj42 = 0;
    objects.obj43 = 0;
    objects.accel_launch_header = 0;
    objects.obj44 = 0;
    objects.accel_startup_instructions = 0;
    objects.accel_lc_status = 0;
    objects.accel_lc_status_go = 0;
    objects.accel_lc_status_fault = 0;
    objects.accel_lc_hint = 0;
    objects.accel_lc_arm_bar = 0;
    objects.accel_lc_fault_reason = 0;
    objects.accel_lc_shadow = 0;
    objects.accel_slip_warn = 0;
    objects.accel_speed = 0;
    objects.accel_slip = 0;
    objects.accel_vcu_state = 0;
    objects.accel_lvbox_pwr = 0;
    deletePageFlowState(2);
}

void tick_screen_accel() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_inv_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_inv_state;
            lv_label_set_text(objects.accel_inv_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 2, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj30);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj30;
            lv_arc_set_value(objects.obj30, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_pdm_11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_pdm_11;
            lv_label_set_text(objects.accel_pdm_11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.accel_apps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_apps;
            lv_bar_set_value(objects.accel_apps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 5, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.accel_bps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_bps;
            lv_bar_set_value(objects.accel_bps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_inverter_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_inverter_off;
            if (new_val) {
                lv_obj_add_flag(objects.accel_inverter_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_inverter_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_pumps_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_pumps_off;
            if (new_val) {
                lv_obj_add_flag(objects.accel_pumps_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_pumps_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 13, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_fans_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_fans_off;
            if (new_val) {
                lv_obj_add_flag(objects.accel_fans_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_fans_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 15, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_tc_off, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_tc_off;
            if (new_val) {
                lv_obj_add_flag(objects.accel_tc_off, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_tc_off, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 17, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_battery_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_battery_warn;
            if (new_val) {
                lv_obj_add_flag(objects.accel_battery_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_battery_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 18, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_battery_crit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_battery_crit;
            if (new_val) {
                lv_obj_add_flag(objects.accel_battery_crit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_battery_crit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 20, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_motor_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_motor_warn;
            if (new_val) {
                lv_obj_add_flag(objects.accel_motor_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_motor_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 21, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_motor_cit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_motor_cit;
            if (new_val) {
                lv_obj_add_flag(objects.accel_motor_cit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_motor_cit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 23, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_inverter_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_inverter_warn;
            if (new_val) {
                lv_obj_add_flag(objects.accel_inverter_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_inverter_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 24, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_inverter_cit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_inverter_cit;
            if (new_val) {
                lv_obj_add_flag(objects.accel_inverter_cit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_inverter_cit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_inverter_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_inverter_temp;
            lv_label_set_text(objects.accel_inverter_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_motor_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_motor_temp;
            lv_label_set_text(objects.accel_motor_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_battery_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_battery_temp;
            lv_label_set_text(objects.accel_battery_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 39, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_soc_percent);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_soc_percent;
            lv_label_set_text(objects.accel_soc_percent, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 39, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_soc_percent, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_soc_percent;
            if (new_val) {
                lv_obj_add_flag(objects.accel_soc_percent, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_soc_percent, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 40, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_soc_percent_warn);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_soc_percent_warn;
            lv_label_set_text(objects.accel_soc_percent_warn, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 40, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_soc_percent_warn;
            if (new_val) {
                lv_obj_add_flag(objects.accel_soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_soc_percent_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 41, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_soc_percent_crit);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_soc_percent_crit;
            lv_label_set_text(objects.accel_soc_percent_crit, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 41, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_soc_percent_crit;
            if (new_val) {
                lv_obj_add_flag(objects.accel_soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_soc_percent_crit, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 52, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_startup_instructions);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_startup_instructions;
            lv_label_set_text(objects.accel_startup_instructions, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 52, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_startup_instructions, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_startup_instructions;
            if (new_val) {
                lv_obj_add_flag(objects.accel_startup_instructions, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_startup_instructions, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 53, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_lc_status);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_lc_status;
            lv_label_set_text(objects.accel_lc_status, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 53, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_status, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_status;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_status, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_status, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 54, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_lc_status_go);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_lc_status_go;
            lv_label_set_text(objects.accel_lc_status_go, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 54, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_status_go, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_status_go;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_status_go, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_status_go, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 55, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_status_fault, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_status_fault;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_status_fault, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_status_fault, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 56, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_lc_hint);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_lc_hint;
            lv_label_set_text(objects.accel_lc_hint, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 56, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_hint, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_hint;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_hint, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_hint, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 57, 4, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.accel_lc_arm_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_arm_bar;
            lv_bar_set_value(objects.accel_lc_arm_bar, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 57, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_arm_bar, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_arm_bar;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_arm_bar, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_arm_bar, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 58, 4, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_lc_fault_reason);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_lc_fault_reason;
            lv_label_set_text(objects.accel_lc_fault_reason, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 58, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_fault_reason, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_fault_reason;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_fault_reason, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_fault_reason, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 59, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_lc_shadow, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_lc_shadow;
            if (new_val) {
                lv_obj_add_flag(objects.accel_lc_shadow, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_lc_shadow, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 60, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.accel_slip_warn, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.accel_slip_warn;
            if (new_val) {
                lv_obj_add_flag(objects.accel_slip_warn, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.accel_slip_warn, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 61, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_speed);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_speed;
            lv_label_set_text(objects.accel_speed, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 62, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_slip);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_slip;
            lv_label_set_text(objects.accel_slip, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 63, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_vcu_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_vcu_state;
            lv_label_set_text(objects.accel_vcu_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 64, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.accel_lvbox_pwr);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.accel_lvbox_pwr;
            lv_label_set_text(objects.accel_lvbox_pwr, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_dyno() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.dyno = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // dyno_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dyno_title = obj;
            lv_obj_set_pos(obj, 20, 8);
            lv_obj_set_size(obj, 400, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Dyno");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj45 = obj;
            lv_obj_set_pos(obj, 0, 98);
            lv_obj_set_size(obj, 800, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // dyno_counter_caption
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dyno_counter_caption = obj;
            lv_obj_set_pos(obj, 0, 112);
            lv_obj_set_size(obj, 800, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Rolling counter");
        }
        {
            // dyno_counter
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dyno_counter = obj;
            lv_obj_set_pos(obj, 0, 158);
            lv_obj_set_size(obj, 800, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_70, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj46 = obj;
            lv_obj_set_pos(obj, 0, 262);
            lv_obj_set_size(obj, 800, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // dyno_state_caption
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dyno_state_caption = obj;
            lv_obj_set_pos(obj, 0, 276);
            lv_obj_set_size(obj, 800, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "VCU state");
        }
        {
            // dyno_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dyno_state = obj;
            lv_obj_set_pos(obj, 10, 322);
            lv_obj_set_size(obj, 780, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_56, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // dyno_no_vcu
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dyno_no_vcu = obj;
            lv_obj_set_pos(obj, 0, 420);
            lv_obj_set_size(obj, 800, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "NO VCU DATA");
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_DYNO - 1);
    
    tick_screen_dyno();
}

void delete_screen_dyno() {
    lv_obj_del(objects.dyno);
    objects.dyno = 0;
    objects.dyno_title = 0;
    objects.obj45 = 0;
    objects.dyno_counter_caption = 0;
    objects.dyno_counter = 0;
    objects.obj46 = 0;
    objects.dyno_state_caption = 0;
    objects.dyno_state = 0;
    objects.dyno_no_vcu = 0;
    deletePageFlowState(3);
}

void tick_screen_dyno() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.dyno_counter);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.dyno_counter;
            lv_label_set_text(objects.dyno_counter, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.dyno_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.dyno_state;
            lv_label_set_text(objects.dyno_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.dyno_no_vcu, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.dyno_no_vcu;
            if (new_val) {
                lv_obj_add_flag(objects.dyno_no_vcu, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.dyno_no_vcu, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_debug() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.debug = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // debug_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.debug_title = obj;
            lv_obj_set_pos(obj, 10, 4);
            lv_obj_set_size(obj, 160, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Debug");
        }
        {
            // debug_vcu
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.debug_vcu = obj;
            lv_obj_set_pos(obj, 170, 8);
            lv_obj_set_size(obj, 470, LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // debug_link_ok
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.debug_link_ok = obj;
            lv_obj_set_pos(obj, 640, 8);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "LINK OK");
        }
        {
            // debug_link_lost
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.debug_link_lost = obj;
            lv_obj_set_pos(obj, 640, 8);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "NO VCU");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj47 = obj;
            lv_obj_set_pos(obj, 0, 50);
            lv_obj_set_size(obj, 800, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj48 = obj;
            lv_obj_set_pos(obj, 265, 53);
            lv_obj_set_size(obj, 3, 427);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj49 = obj;
            lv_obj_set_pos(obj, 530, 53);
            lv_obj_set_size(obj, 3, 427);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj50 = obj;
            lv_obj_set_pos(obj, 10, 58);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "VCU");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj51 = obj;
            lv_obj_set_pos(obj, 10, 94);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj52 = obj;
            lv_obj_set_pos(obj, 10, 119);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj53 = obj;
            lv_obj_set_pos(obj, 10, 144);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj54 = obj;
            lv_obj_set_pos(obj, 10, 169);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj55 = obj;
            lv_obj_set_pos(obj, 10, 194);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj56 = obj;
            lv_obj_set_pos(obj, 10, 219);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj57 = obj;
            lv_obj_set_pos(obj, 10, 244);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj58 = obj;
            lv_obj_set_pos(obj, 10, 269);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj59 = obj;
            lv_obj_set_pos(obj, 10, 298);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Dash CAN");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj60 = obj;
            lv_obj_set_pos(obj, 10, 334);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj61 = obj;
            lv_obj_set_pos(obj, 10, 359);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj62 = obj;
            lv_obj_set_pos(obj, 10, 384);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj63 = obj;
            lv_obj_set_pos(obj, 275, 58);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Shutdown");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj64 = obj;
            lv_obj_set_pos(obj, 275, 94);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj65 = obj;
            lv_obj_set_pos(obj, 275, 119);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj66 = obj;
            lv_obj_set_pos(obj, 275, 144);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj67 = obj;
            lv_obj_set_pos(obj, 275, 169);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj68 = obj;
            lv_obj_set_pos(obj, 275, 194);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj69 = obj;
            lv_obj_set_pos(obj, 275, 219);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj70 = obj;
            lv_obj_set_pos(obj, 275, 244);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj71 = obj;
            lv_obj_set_pos(obj, 275, 269);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj72 = obj;
            lv_obj_set_pos(obj, 275, 294);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj73 = obj;
            lv_obj_set_pos(obj, 275, 319);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj74 = obj;
            lv_obj_set_pos(obj, 275, 348);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj75 = obj;
            lv_obj_set_pos(obj, 275, 384);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj76 = obj;
            lv_obj_set_pos(obj, 540, 58);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "APPS / BPS");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj77 = obj;
            lv_obj_set_pos(obj, 540, 94);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj78 = obj;
            lv_obj_set_pos(obj, 540, 119);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj79 = obj;
            lv_obj_set_pos(obj, 540, 144);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj80 = obj;
            lv_obj_set_pos(obj, 540, 169);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj81 = obj;
            lv_obj_set_pos(obj, 540, 194);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj82 = obj;
            lv_obj_set_pos(obj, 540, 219);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj83 = obj;
            lv_obj_set_pos(obj, 540, 248);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Temps (C)");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj84 = obj;
            lv_obj_set_pos(obj, 540, 284);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj85 = obj;
            lv_obj_set_pos(obj, 540, 309);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj86 = obj;
            lv_obj_set_pos(obj, 540, 334);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj87 = obj;
            lv_obj_set_pos(obj, 540, 359);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj88 = obj;
            lv_obj_set_pos(obj, 540, 388);
            lv_obj_set_size(obj, 255, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Power");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj89 = obj;
            lv_obj_set_pos(obj, 540, 424);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj90 = obj;
            lv_obj_set_pos(obj, 540, 449);
            lv_obj_set_size(obj, 255, 24);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_DEBUG - 1);
    
    tick_screen_debug();
}

void delete_screen_debug() {
    lv_obj_del(objects.debug);
    objects.debug = 0;
    objects.debug_title = 0;
    objects.debug_vcu = 0;
    objects.debug_link_ok = 0;
    objects.debug_link_lost = 0;
    objects.obj47 = 0;
    objects.obj48 = 0;
    objects.obj49 = 0;
    objects.obj50 = 0;
    objects.obj51 = 0;
    objects.obj52 = 0;
    objects.obj53 = 0;
    objects.obj54 = 0;
    objects.obj55 = 0;
    objects.obj56 = 0;
    objects.obj57 = 0;
    objects.obj58 = 0;
    objects.obj59 = 0;
    objects.obj60 = 0;
    objects.obj61 = 0;
    objects.obj62 = 0;
    objects.obj63 = 0;
    objects.obj64 = 0;
    objects.obj65 = 0;
    objects.obj66 = 0;
    objects.obj67 = 0;
    objects.obj68 = 0;
    objects.obj69 = 0;
    objects.obj70 = 0;
    objects.obj71 = 0;
    objects.obj72 = 0;
    objects.obj73 = 0;
    objects.obj74 = 0;
    objects.obj75 = 0;
    objects.obj76 = 0;
    objects.obj77 = 0;
    objects.obj78 = 0;
    objects.obj79 = 0;
    objects.obj80 = 0;
    objects.obj81 = 0;
    objects.obj82 = 0;
    objects.obj83 = 0;
    objects.obj84 = 0;
    objects.obj85 = 0;
    objects.obj86 = 0;
    objects.obj87 = 0;
    objects.obj88 = 0;
    objects.obj89 = 0;
    objects.obj90 = 0;
    deletePageFlowState(4);
}

void tick_screen_debug() {
    void *flowState = getFlowState(0, 4);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.debug_vcu);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.debug_vcu;
            lv_label_set_text(objects.debug_vcu, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 3, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.debug_link_ok, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.debug_link_ok;
            if (new_val) {
                lv_obj_add_flag(objects.debug_link_ok, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.debug_link_ok, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 4, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.debug_link_lost, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.debug_link_lost;
            if (new_val) {
                lv_obj_add_flag(objects.debug_link_lost, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.debug_link_lost, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj51);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj51;
            lv_label_set_text(objects.obj51, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj52);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj52;
            lv_label_set_text(objects.obj52, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj53);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj53;
            lv_label_set_text(objects.obj53, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj54);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj54;
            lv_label_set_text(objects.obj54, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj55);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj55;
            lv_label_set_text(objects.obj55, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj56);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj56;
            lv_label_set_text(objects.obj56, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj57);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj57;
            lv_label_set_text(objects.obj57, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 16, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj58);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj58;
            lv_label_set_text(objects.obj58, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj60);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj60;
            lv_label_set_text(objects.obj60, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj61);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj61;
            lv_label_set_text(objects.obj61, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj62);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj62;
            lv_label_set_text(objects.obj62, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 22, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj64);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj64;
            lv_label_set_text(objects.obj64, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj65);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj65;
            lv_label_set_text(objects.obj65, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj66);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj66;
            lv_label_set_text(objects.obj66, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 25, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj67);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj67;
            lv_label_set_text(objects.obj67, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 26, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj68);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj68;
            lv_label_set_text(objects.obj68, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj69);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj69;
            lv_label_set_text(objects.obj69, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 28, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj70);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj70;
            lv_label_set_text(objects.obj70, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 29, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj71);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj71;
            lv_label_set_text(objects.obj71, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 30, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj72);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj72;
            lv_label_set_text(objects.obj72, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 31, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj73);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj73;
            lv_label_set_text(objects.obj73, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 33, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj75);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj75;
            lv_label_set_text(objects.obj75, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 35, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj77);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj77;
            lv_label_set_text(objects.obj77, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 36, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj78);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj78;
            lv_label_set_text(objects.obj78, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 37, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj79);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj79;
            lv_label_set_text(objects.obj79, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 38, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj80);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj80;
            lv_label_set_text(objects.obj80, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 39, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj81);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj81;
            lv_label_set_text(objects.obj81, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 40, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj82);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj82;
            lv_label_set_text(objects.obj82, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 42, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj84);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj84;
            lv_label_set_text(objects.obj84, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 43, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj85);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj85;
            lv_label_set_text(objects.obj85, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 44, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj86);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj86;
            lv_label_set_text(objects.obj86, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 45, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj87);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj87;
            lv_label_set_text(objects.obj87, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 47, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj89);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj89;
            lv_label_set_text(objects.obj89, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 48, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj90);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj90;
            lv_label_set_text(objects.obj90, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_sponsors() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.sponsors = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // sponsors_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sponsors_title = obj;
            lv_obj_set_pos(obj, 0, 22);
            lv_obj_set_size(obj, 800, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &ui_font_b612_36, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Thank you to our Platinum Sponsors");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj91 = obj;
            lv_obj_set_pos(obj, 40, 78);
            lv_obj_set_size(obj, 720, 3);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_logo_uos
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.sponsors_logo_uos = obj;
            lv_obj_set_pos(obj, 160, 196);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_sponsor_uos);
        }
        {
            // sponsors_dot_0
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_0 = obj;
            lv_obj_set_pos(obj, 333, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_lighten(lv_color_hex(0x000000), 191), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_dot_on_0
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_on_0 = obj;
            lv_obj_set_pos(obj, 333, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_logo_sfs
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.sponsors_logo_sfs = obj;
            lv_obj_set_pos(obj, 285, 132);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_sponsor_sfs);
        }
        {
            // sponsors_dot_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_1 = obj;
            lv_obj_set_pos(obj, 363, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_lighten(lv_color_hex(0x000000), 191), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_dot_on_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_on_1 = obj;
            lv_obj_set_pos(obj, 363, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_logo_vector
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.sponsors_logo_vector = obj;
            lv_obj_set_pos(obj, 160, 190);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_sponsor_vector);
        }
        {
            // sponsors_dot_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_2 = obj;
            lv_obj_set_pos(obj, 393, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_lighten(lv_color_hex(0x000000), 191), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_dot_on_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_on_2 = obj;
            lv_obj_set_pos(obj, 393, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_logo_rfpro
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.sponsors_logo_rfpro = obj;
            lv_obj_set_pos(obj, 179, 132);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_sponsor_rfpro);
        }
        {
            // sponsors_dot_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_3 = obj;
            lv_obj_set_pos(obj, 423, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_lighten(lv_color_hex(0x000000), 191), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_dot_on_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_on_3 = obj;
            lv_obj_set_pos(obj, 423, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_logo_about_energy
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.sponsors_logo_about_energy = obj;
            lv_obj_set_pos(obj, 160, 220);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_sponsor_about_energy);
        }
        {
            // sponsors_dot_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_4 = obj;
            lv_obj_set_pos(obj, 453, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_lighten(lv_color_hex(0x000000), 191), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sponsors_dot_on_4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.sponsors_dot_on_4 = obj;
            lv_obj_set_pos(obj, 453, 428);
            lv_obj_set_size(obj, 14, 14);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    eez_flow_delete_screen_on_unload(SCREEN_ID_SPONSORS - 1);
    
    tick_screen_sponsors();
}

void delete_screen_sponsors() {
    lv_obj_del(objects.sponsors);
    objects.sponsors = 0;
    objects.sponsors_title = 0;
    objects.obj91 = 0;
    objects.sponsors_logo_uos = 0;
    objects.sponsors_dot_0 = 0;
    objects.sponsors_dot_on_0 = 0;
    objects.sponsors_logo_sfs = 0;
    objects.sponsors_dot_1 = 0;
    objects.sponsors_dot_on_1 = 0;
    objects.sponsors_logo_vector = 0;
    objects.sponsors_dot_2 = 0;
    objects.sponsors_dot_on_2 = 0;
    objects.sponsors_logo_rfpro = 0;
    objects.sponsors_dot_3 = 0;
    objects.sponsors_dot_on_3 = 0;
    objects.sponsors_logo_about_energy = 0;
    objects.sponsors_dot_4 = 0;
    objects.sponsors_dot_on_4 = 0;
    deletePageFlowState(5);
}

void tick_screen_sponsors() {
    void *flowState = getFlowState(0, 5);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 3, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_logo_uos, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_logo_uos;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_logo_uos, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_logo_uos, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 5, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_dot_on_0, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_dot_on_0;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_dot_on_0, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_dot_on_0, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 6, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_logo_sfs, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_logo_sfs;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_logo_sfs, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_logo_sfs, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 8, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_dot_on_1, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_dot_on_1;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_dot_on_1, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_dot_on_1, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 9, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_logo_vector, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_logo_vector;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_logo_vector, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_logo_vector, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 11, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_dot_on_2, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_dot_on_2;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_dot_on_2, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_dot_on_2, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 12, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_logo_rfpro, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_logo_rfpro;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_logo_rfpro, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_logo_rfpro, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 14, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_dot_on_3, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_dot_on_3;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_dot_on_3, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_dot_on_3, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 15, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_logo_about_energy, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_logo_about_energy;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_logo_about_energy, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_logo_about_energy, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 17, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.sponsors_dot_on_4, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.sponsors_dot_on_4;
            if (new_val) {
                lv_obj_add_flag(objects.sponsors_dot_on_4, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_clear_flag(objects.sponsors_dot_on_4, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*create_screen_func_t)();
create_screen_func_t create_screen_funcs[] = {
    create_screen_main,
    create_screen_skidpad,
    create_screen_accel,
    create_screen_dyno,
    create_screen_debug,
    create_screen_sponsors,
};
void create_screen(int screen_index) {
    create_screen_funcs[screen_index]();
}
void create_screen_by_id(enum ScreensEnum screenId) {
    create_screen_funcs[screenId - 1]();
}

typedef void (*delete_screen_func_t)();
delete_screen_func_t delete_screen_funcs[] = {
    delete_screen_main,
    delete_screen_skidpad,
    delete_screen_accel,
    delete_screen_dyno,
    delete_screen_debug,
    delete_screen_sponsors,
};
void delete_screen(int screen_index) {
    delete_screen_funcs[screen_index]();
}
void delete_screen_by_id(enum ScreensEnum screenId) {
    delete_screen_funcs[screenId - 1]();
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_skidpad,
    tick_screen_accel,
    tick_screen_dyno,
    tick_screen_debug,
    tick_screen_sponsors,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 6) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "b612_14", &ui_font_b612_14 },
    { "b612_22", &ui_font_b612_22 },
    { "b612_30", &ui_font_b612_30 },
    { "b612_36", &ui_font_b612_36 },
    { "b612_46", &ui_font_b612_46 },
    { "b612_56", &ui_font_b612_56 },
    { "b612_70", &ui_font_b612_70 },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

void change_color_theme(uint32_t theme_index) {
    {
        if (objects.main) lv_obj_set_style_bg_color(objects.main, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.lvbox_pwr) lv_obj_set_style_text_color(objects.lvbox_pwr, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.vcu_state) lv_obj_set_style_text_color(objects.vcu_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inv_state) lv_obj_set_style_text_color(objects.inv_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.pdm_11) lv_obj_set_style_text_color(objects.pdm_11, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.lap_number) lv_obj_set_style_text_color(objects.lap_number, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj2) lv_obj_set_style_text_color(objects.obj2, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj2) lv_obj_set_style_border_color(objects.obj2, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_on) lv_obj_set_style_bg_color(objects.inverter_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_off) lv_obj_set_style_bg_color(objects.inverter_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.pumps_on) lv_obj_set_style_bg_color(objects.pumps_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.pumps_off) lv_obj_set_style_bg_color(objects.pumps_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.fans_on) lv_obj_set_style_bg_color(objects.fans_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.fans_off) lv_obj_set_style_bg_color(objects.fans_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.tc_on) lv_obj_set_style_bg_color(objects.tc_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.tc_off) lv_obj_set_style_bg_color(objects.tc_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.battery_ok) lv_obj_set_style_bg_color(objects.battery_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.battery_warn) lv_obj_set_style_bg_color(objects.battery_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.battery_crit) lv_obj_set_style_bg_color(objects.battery_crit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.motor_ok) lv_obj_set_style_bg_color(objects.motor_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.motor_warn) lv_obj_set_style_bg_color(objects.motor_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.motor_cit) lv_obj_set_style_bg_color(objects.motor_cit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_ok) lv_obj_set_style_bg_color(objects.inverter_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_warn) lv_obj_set_style_bg_color(objects.inverter_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_cit) lv_obj_set_style_bg_color(objects.inverter_cit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj3) lv_obj_set_style_border_color(objects.obj3, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_temp) lv_obj_set_style_text_color(objects.inverter_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_temp_4) lv_obj_set_style_text_color(objects.inverter_temp_4, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_temp_5) lv_obj_set_style_text_color(objects.inverter_temp_5, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.motor_temp) lv_obj_set_style_text_color(objects.motor_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_temp_6) lv_obj_set_style_text_color(objects.inverter_temp_6, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.battery_temp) lv_obj_set_style_text_color(objects.battery_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj4) lv_obj_set_style_border_color(objects.obj4, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj5) lv_obj_set_style_border_color(objects.obj5, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj6) lv_obj_set_style_border_color(objects.obj6, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj7) lv_obj_set_style_border_color(objects.obj7, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj8) lv_obj_set_style_bg_color(objects.obj8, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj8) lv_obj_set_style_border_color(objects.obj8, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj9) lv_obj_set_style_text_color(objects.obj9, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj9) lv_obj_set_style_bg_color(objects.obj9, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj9) lv_obj_set_style_border_color(objects.obj9, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj10) lv_obj_set_style_text_color(objects.obj10, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj10) lv_obj_set_style_bg_color(objects.obj10, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj10) lv_obj_set_style_border_color(objects.obj10, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj11) lv_obj_set_style_text_color(objects.obj11, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj11) lv_obj_set_style_bg_color(objects.obj11, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj11) lv_obj_set_style_border_color(objects.obj11, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc_percent) lv_obj_set_style_text_color(objects.soc_percent, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc_percent_warn) lv_obj_set_style_text_color(objects.soc_percent_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc_percent_crit) lv_obj_set_style_text_color(objects.soc_percent_crit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.mode) lv_obj_set_style_text_color(objects.mode, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.inverter_switch_label) lv_obj_set_style_text_color(objects.inverter_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.pumps_switch_label) lv_obj_set_style_text_color(objects.pumps_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.fans_switch_label) lv_obj_set_style_text_color(objects.fans_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.tc_switch_label) lv_obj_set_style_text_color(objects.tc_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj12) lv_obj_set_style_text_color(objects.obj12, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj12) lv_obj_set_style_border_color(objects.obj12, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj13) lv_obj_set_style_text_color(objects.obj13, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj13) lv_obj_set_style_border_color(objects.obj13, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj14) lv_obj_set_style_text_color(objects.obj14, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj14) lv_obj_set_style_border_color(objects.obj14, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.startup_instructions) lv_obj_set_style_text_color(objects.startup_instructions, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc_target_text) lv_obj_set_style_text_color(objects.soc_target_text, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc_target_text_neg) lv_obj_set_style_text_color(objects.soc_target_text_neg, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc) lv_obj_set_style_text_color(objects.soc, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.soc__) lv_obj_set_style_text_color(objects.soc__, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        if (objects.skidpad) lv_obj_set_style_bg_color(objects.skidpad, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_lvbox_pwr) lv_obj_set_style_text_color(objects.skidpad_lvbox_pwr, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_vcu_state) lv_obj_set_style_text_color(objects.skidpad_vcu_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inv_state) lv_obj_set_style_text_color(objects.skidpad_inv_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_pdm_11) lv_obj_set_style_text_color(objects.skidpad_pdm_11, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_lap_number) lv_obj_set_style_text_color(objects.skidpad_lap_number, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj17) lv_obj_set_style_text_color(objects.obj17, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj17) lv_obj_set_style_border_color(objects.obj17, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_on) lv_obj_set_style_bg_color(objects.skidpad_inverter_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_off) lv_obj_set_style_bg_color(objects.skidpad_inverter_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_pumps_on) lv_obj_set_style_bg_color(objects.skidpad_pumps_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_pumps_off) lv_obj_set_style_bg_color(objects.skidpad_pumps_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_fans_on) lv_obj_set_style_bg_color(objects.skidpad_fans_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_fans_off) lv_obj_set_style_bg_color(objects.skidpad_fans_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_tc_on) lv_obj_set_style_bg_color(objects.skidpad_tc_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_tc_off) lv_obj_set_style_bg_color(objects.skidpad_tc_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_battery_ok) lv_obj_set_style_bg_color(objects.skidpad_battery_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_battery_warn) lv_obj_set_style_bg_color(objects.skidpad_battery_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_battery_crit) lv_obj_set_style_bg_color(objects.skidpad_battery_crit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_motor_ok) lv_obj_set_style_bg_color(objects.skidpad_motor_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_motor_warn) lv_obj_set_style_bg_color(objects.skidpad_motor_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_motor_cit) lv_obj_set_style_bg_color(objects.skidpad_motor_cit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_ok) lv_obj_set_style_bg_color(objects.skidpad_inverter_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_warn) lv_obj_set_style_bg_color(objects.skidpad_inverter_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_cit) lv_obj_set_style_bg_color(objects.skidpad_inverter_cit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj18) lv_obj_set_style_border_color(objects.obj18, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_temp) lv_obj_set_style_text_color(objects.skidpad_inverter_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_temp_4) lv_obj_set_style_text_color(objects.skidpad_inverter_temp_4, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_temp_5) lv_obj_set_style_text_color(objects.skidpad_inverter_temp_5, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_motor_temp) lv_obj_set_style_text_color(objects.skidpad_motor_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_temp_6) lv_obj_set_style_text_color(objects.skidpad_inverter_temp_6, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_battery_temp) lv_obj_set_style_text_color(objects.skidpad_battery_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj19) lv_obj_set_style_border_color(objects.obj19, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj20) lv_obj_set_style_border_color(objects.obj20, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj21) lv_obj_set_style_border_color(objects.obj21, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj22) lv_obj_set_style_border_color(objects.obj22, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj23) lv_obj_set_style_bg_color(objects.obj23, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj23) lv_obj_set_style_border_color(objects.obj23, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj24) lv_obj_set_style_text_color(objects.obj24, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj24) lv_obj_set_style_bg_color(objects.obj24, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj24) lv_obj_set_style_border_color(objects.obj24, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj25) lv_obj_set_style_text_color(objects.obj25, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj25) lv_obj_set_style_bg_color(objects.obj25, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj25) lv_obj_set_style_border_color(objects.obj25, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj26) lv_obj_set_style_text_color(objects.obj26, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj26) lv_obj_set_style_bg_color(objects.obj26, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj26) lv_obj_set_style_border_color(objects.obj26, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_soc_percent) lv_obj_set_style_text_color(objects.skidpad_soc_percent, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_soc_percent_warn) lv_obj_set_style_text_color(objects.skidpad_soc_percent_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_soc_percent_crit) lv_obj_set_style_text_color(objects.skidpad_soc_percent_crit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_mode) lv_obj_set_style_text_color(objects.skidpad_mode, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_inverter_switch_label) lv_obj_set_style_text_color(objects.skidpad_inverter_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_pumps_switch_label) lv_obj_set_style_text_color(objects.skidpad_pumps_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_fans_switch_label) lv_obj_set_style_text_color(objects.skidpad_fans_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_tc_switch_label) lv_obj_set_style_text_color(objects.skidpad_tc_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj27) lv_obj_set_style_text_color(objects.obj27, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj27) lv_obj_set_style_border_color(objects.obj27, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj28) lv_obj_set_style_text_color(objects.obj28, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj28) lv_obj_set_style_border_color(objects.obj28, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj29) lv_obj_set_style_text_color(objects.obj29, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj29) lv_obj_set_style_border_color(objects.obj29, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_startup_instructions) lv_obj_set_style_text_color(objects.skidpad_startup_instructions, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.skidpad_soc) lv_obj_set_style_text_color(objects.skidpad_soc, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        if (objects.accel) lv_obj_set_style_bg_color(objects.accel, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inv_state) lv_obj_set_style_text_color(objects.accel_inv_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_pdm_11) lv_obj_set_style_text_color(objects.accel_pdm_11, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj32) lv_obj_set_style_text_color(objects.obj32, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj32) lv_obj_set_style_border_color(objects.obj32, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_on) lv_obj_set_style_bg_color(objects.accel_inverter_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_off) lv_obj_set_style_bg_color(objects.accel_inverter_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_pumps_on) lv_obj_set_style_bg_color(objects.accel_pumps_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_pumps_off) lv_obj_set_style_bg_color(objects.accel_pumps_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_fans_on) lv_obj_set_style_bg_color(objects.accel_fans_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_fans_off) lv_obj_set_style_bg_color(objects.accel_fans_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_tc_on) lv_obj_set_style_bg_color(objects.accel_tc_on, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_tc_off) lv_obj_set_style_bg_color(objects.accel_tc_off, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_battery_ok) lv_obj_set_style_bg_color(objects.accel_battery_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_battery_warn) lv_obj_set_style_bg_color(objects.accel_battery_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_battery_crit) lv_obj_set_style_bg_color(objects.accel_battery_crit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_motor_ok) lv_obj_set_style_bg_color(objects.accel_motor_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_motor_warn) lv_obj_set_style_bg_color(objects.accel_motor_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_motor_cit) lv_obj_set_style_bg_color(objects.accel_motor_cit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_ok) lv_obj_set_style_bg_color(objects.accel_inverter_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_warn) lv_obj_set_style_bg_color(objects.accel_inverter_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_cit) lv_obj_set_style_bg_color(objects.accel_inverter_cit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj33) lv_obj_set_style_border_color(objects.obj33, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_temp) lv_obj_set_style_text_color(objects.accel_inverter_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_temp_4) lv_obj_set_style_text_color(objects.accel_inverter_temp_4, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_temp_5) lv_obj_set_style_text_color(objects.accel_inverter_temp_5, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_motor_temp) lv_obj_set_style_text_color(objects.accel_motor_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_temp_6) lv_obj_set_style_text_color(objects.accel_inverter_temp_6, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_battery_temp) lv_obj_set_style_text_color(objects.accel_battery_temp, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj34) lv_obj_set_style_border_color(objects.obj34, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj35) lv_obj_set_style_border_color(objects.obj35, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj36) lv_obj_set_style_border_color(objects.obj36, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj37) lv_obj_set_style_border_color(objects.obj37, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj38) lv_obj_set_style_border_color(objects.obj38, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj39) lv_obj_set_style_bg_color(objects.obj39, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj39) lv_obj_set_style_border_color(objects.obj39, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj40) lv_obj_set_style_text_color(objects.obj40, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj40) lv_obj_set_style_bg_color(objects.obj40, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj40) lv_obj_set_style_border_color(objects.obj40, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_soc_percent) lv_obj_set_style_text_color(objects.accel_soc_percent, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_soc_percent_warn) lv_obj_set_style_text_color(objects.accel_soc_percent_warn, lv_color_hex(theme_colors[theme_index][3]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_soc_percent_crit) lv_obj_set_style_text_color(objects.accel_soc_percent_crit, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_mode) lv_obj_set_style_text_color(objects.accel_mode, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_inverter_switch_label) lv_obj_set_style_text_color(objects.accel_inverter_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_pumps_switch_label) lv_obj_set_style_text_color(objects.accel_pumps_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_fans_switch_label) lv_obj_set_style_text_color(objects.accel_fans_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_tc_switch_label) lv_obj_set_style_text_color(objects.accel_tc_switch_label, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj41) lv_obj_set_style_text_color(objects.obj41, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj41) lv_obj_set_style_border_color(objects.obj41, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj42) lv_obj_set_style_text_color(objects.obj42, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj42) lv_obj_set_style_border_color(objects.obj42, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj43) lv_obj_set_style_text_color(objects.obj43, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj43) lv_obj_set_style_border_color(objects.obj43, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_launch_header) lv_obj_set_style_text_color(objects.accel_launch_header, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj44) lv_obj_set_style_border_color(objects.obj44, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_startup_instructions) lv_obj_set_style_text_color(objects.accel_startup_instructions, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_status) lv_obj_set_style_text_color(objects.accel_lc_status, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_status_go) lv_obj_set_style_text_color(objects.accel_lc_status_go, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_status_fault) lv_obj_set_style_text_color(objects.accel_lc_status_fault, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_hint) lv_obj_set_style_text_color(objects.accel_lc_hint, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_arm_bar) lv_obj_set_style_bg_color(objects.accel_lc_arm_bar, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_arm_bar) lv_obj_set_style_bg_color(objects.accel_lc_arm_bar, lv_color_hex(theme_colors[theme_index][2]), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        if (objects.accel_lc_fault_reason) lv_obj_set_style_text_color(objects.accel_lc_fault_reason, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lc_shadow) lv_obj_set_style_text_color(objects.accel_lc_shadow, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_slip_warn) lv_obj_set_style_bg_color(objects.accel_slip_warn, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_speed) lv_obj_set_style_text_color(objects.accel_speed, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_slip) lv_obj_set_style_text_color(objects.accel_slip, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_vcu_state) lv_obj_set_style_text_color(objects.accel_vcu_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.accel_lvbox_pwr) lv_obj_set_style_text_color(objects.accel_lvbox_pwr, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        if (objects.dyno) lv_obj_set_style_bg_color(objects.dyno, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.dyno_title) lv_obj_set_style_text_color(objects.dyno_title, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj45) lv_obj_set_style_border_color(objects.obj45, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.dyno_counter_caption) lv_obj_set_style_text_color(objects.dyno_counter_caption, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.dyno_counter) lv_obj_set_style_text_color(objects.dyno_counter, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj46) lv_obj_set_style_border_color(objects.obj46, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.dyno_state_caption) lv_obj_set_style_text_color(objects.dyno_state_caption, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.dyno_state) lv_obj_set_style_text_color(objects.dyno_state, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.dyno_no_vcu) lv_obj_set_style_text_color(objects.dyno_no_vcu, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    {
        if (objects.debug) lv_obj_set_style_bg_color(objects.debug, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.debug_title) lv_obj_set_style_text_color(objects.debug_title, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.debug_vcu) lv_obj_set_style_text_color(objects.debug_vcu, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.debug_link_ok) lv_obj_set_style_text_color(objects.debug_link_ok, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.debug_link_lost) lv_obj_set_style_text_color(objects.debug_link_lost, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj47) lv_obj_set_style_border_color(objects.obj47, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj48) lv_obj_set_style_border_color(objects.obj48, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj49) lv_obj_set_style_border_color(objects.obj49, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj50) lv_obj_set_style_text_color(objects.obj50, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj51) lv_obj_set_style_text_color(objects.obj51, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj52) lv_obj_set_style_text_color(objects.obj52, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj53) lv_obj_set_style_text_color(objects.obj53, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj54) lv_obj_set_style_text_color(objects.obj54, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj55) lv_obj_set_style_text_color(objects.obj55, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj56) lv_obj_set_style_text_color(objects.obj56, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj57) lv_obj_set_style_text_color(objects.obj57, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj58) lv_obj_set_style_text_color(objects.obj58, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj59) lv_obj_set_style_text_color(objects.obj59, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj60) lv_obj_set_style_text_color(objects.obj60, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj61) lv_obj_set_style_text_color(objects.obj61, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj62) lv_obj_set_style_text_color(objects.obj62, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj63) lv_obj_set_style_text_color(objects.obj63, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj64) lv_obj_set_style_text_color(objects.obj64, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj65) lv_obj_set_style_text_color(objects.obj65, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj66) lv_obj_set_style_text_color(objects.obj66, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj67) lv_obj_set_style_text_color(objects.obj67, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj68) lv_obj_set_style_text_color(objects.obj68, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj69) lv_obj_set_style_text_color(objects.obj69, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj70) lv_obj_set_style_text_color(objects.obj70, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj71) lv_obj_set_style_text_color(objects.obj71, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj72) lv_obj_set_style_text_color(objects.obj72, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj73) lv_obj_set_style_text_color(objects.obj73, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj74) lv_obj_set_style_text_color(objects.obj74, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj75) lv_obj_set_style_text_color(objects.obj75, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj76) lv_obj_set_style_text_color(objects.obj76, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj77) lv_obj_set_style_text_color(objects.obj77, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj78) lv_obj_set_style_text_color(objects.obj78, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj79) lv_obj_set_style_text_color(objects.obj79, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj80) lv_obj_set_style_text_color(objects.obj80, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj81) lv_obj_set_style_text_color(objects.obj81, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj82) lv_obj_set_style_text_color(objects.obj82, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj83) lv_obj_set_style_text_color(objects.obj83, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj84) lv_obj_set_style_text_color(objects.obj84, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj85) lv_obj_set_style_text_color(objects.obj85, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj86) lv_obj_set_style_text_color(objects.obj86, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj87) lv_obj_set_style_text_color(objects.obj87, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj88) lv_obj_set_style_text_color(objects.obj88, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj89) lv_obj_set_style_text_color(objects.obj89, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        if (objects.obj90) lv_obj_set_style_text_color(objects.obj90, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    if (objects.main) lv_obj_invalidate(objects.main);
    if (objects.skidpad) lv_obj_invalidate(objects.skidpad);
    if (objects.accel) lv_obj_invalidate(objects.accel);
    if (objects.dyno) lv_obj_invalidate(objects.dyno);
    if (objects.debug) lv_obj_invalidate(objects.debug);
    if (objects.sponsors) lv_obj_invalidate(objects.sponsors);
}
static const char *theme_names[] = { "dash-white-bg", "dash-black-bg" };
uint32_t theme_colors[2][11] = {
    { 0xffffffff, 0xff000000, 0xff19d35b, 0xffff9600, 0xffff3b30, 0xff000000, 0xff000000, 0xff0057ff, 0xff333333, 0xffa8d8f0, 0xffa8aca8 },
    { 0xff000000, 0xffffffff, 0xff109a3c, 0xffd97000, 0xffe0352a, 0xff000000, 0xff000000, 0xff0057ff, 0xff333333, 0xff0d3550, 0xff3a3a3a },
};

//
//
//

void create_screens() {
    
    eez_flow_init_fonts(fonts, sizeof(fonts) / sizeof(ext_font_desc_t));
    
    eez_flow_init_themes(theme_names, sizeof(theme_names) / sizeof(const char *), change_color_theme, &theme_colors[0][0], sizeof(theme_colors[0]) / sizeof(uint32_t));

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    eez_flow_set_create_screen_func(create_screen);
    eez_flow_set_delete_screen_func(delete_screen);
    
    // Create screens
    create_screen_main();
}