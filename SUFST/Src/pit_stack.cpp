/* Pit Stack, firmware side: decides when the game may be on screen, turns the steering wheel and pedals
 * into game inputs, draws the blocks into the game_well box of the Game screen, and feeds the score and
 * message text to the screen. The game itself, and how it is played, is in pit_stack.h. */

#include <stdint.h>

#include "main.h"

#include "lvgl/lvgl.h"

#include "can_rx_handlers.h"
#include "dash_diag.h"
#include "eez-flow.h"
#include "pit_stack.h"
#include "pit_stack_fw.h"
#include "screens.h"
#include "ui.h"
#include "vars.h"

static ps_game_t game;
static lv_obj_t *well; /* the game_well box the draw function is attached to, while the Game screen exists */
static bool throttle_was_down;

/* The game is only ever shown with the car parked and dead:
 *   - the VCU is talking to us and says "TS Button Wait" (state 0: tractive system off, nobody has asked for it)
 *   - no tractive system voltage detected
 *   - wheel speeds are arriving and all four are zero
 * Anything else (including losing the VCU) and the dash is back on its normal screen on the next pass. */
extern "C" bool pit_stack_allowed(void)
{
    const double still = 1.0; /* wheel speed below this counts as stopped (sensor noise) */

    return get_var_vcu_link_ok() && get_raw_vcu_ctrl_state() == 0 && !get_var_ts_detected() &&
           dash_diag_wheel_speeds_fresh() && get_var_wheel_fl_speed() < still && get_var_wheel_fr_speed() < still &&
           get_var_wheel_rl_speed() < still && get_var_wheel_rr_speed() < still;
}

static void fill_square(lv_draw_ctx_t *ctx, lv_draw_rect_dsc_t *dsc, const lv_area_t *box, lv_coord_t size, int x,
                        int y, uint8_t colour)
{
    /* block colours: the dash theme's Ok, Warn, Crit and Text */
    static const uint8_t theme_colour[PS_COLOURS] = {COLOR_ID_OK, COLOR_ID_WARN, COLOR_ID_CRIT, COLOR_ID_TEXT};

    lv_area_t a;
    a.x1 = (lv_coord_t)(box->x1 + x * size + 1); /* 1 px gap all round, so the squares read as squares */
    a.y1 = (lv_coord_t)(box->y1 + y * size + 1);
    a.x2 = (lv_coord_t)(a.x1 + size - 3);
    a.y2 = (lv_coord_t)(a.y1 + size - 3);
    dsc->bg_color = lv_color_hex(theme_colors[eez_flow_get_selected_theme_index()][theme_colour[colour - 1]]);
    lv_draw_rect(ctx, dsc, &a);
}

/* Draws the landed squares and the falling block inside game_well, as big as fit, centred */
static void draw_well(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *ctx = lv_event_get_draw_ctx(e);

    lv_area_t box;
    lv_obj_get_content_coords(obj, &box);
    lv_coord_t size = LV_MIN(lv_area_get_width(&box) / PS_W, lv_area_get_height(&box) / PS_H);
    if (size < 4)
    {
        return;
    }
    box.x1 = (lv_coord_t)(box.x1 + (lv_area_get_width(&box) - size * PS_W) / 2);
    box.y1 = (lv_coord_t)(box.y1 + (lv_area_get_height(&box) - size * PS_H) / 2);

    lv_draw_rect_dsc_t dsc;
    lv_draw_rect_dsc_init(&dsc);

    for (int y = 0; y < PS_H; y++)
    {
        for (int x = 0; x < PS_W; x++)
        {
            if (game.cell[y][x])
            {
                fill_square(ctx, &dsc, &box, size, x, y, game.cell[y][x]);
            }
        }
    }
    if (game.state == PS_PLAYING || game.state == PS_PAUSED)
    {
        for (int by = 0; by < 4; by++)
        {
            for (int bx = 0; bx < 4; bx++)
            {
                if (ps_mask_at(game.mask, bx, by))
                {
                    fill_square(ctx, &dsc, &box, size, game.x + bx, game.y + by, game.colour);
                }
            }
        }
    }
}

static void well_deleted(lv_event_t *e)
{
    (void)e;
    well = NULL;
}

/* Call every pass of the UI loop */
extern "C" void pit_stack_tick(void)
{
    if (objects.game_well == NULL || lv_scr_act() != objects.game)
    {
        ps_hide(&game); /* not on screen: a game in progress waits */
        return;
    }
    if (well != objects.game_well)
    {
        well = objects.game_well; /* the Game screen has just been made */
        lv_obj_add_event_cb(well, draw_well, LV_EVENT_DRAW_MAIN_END, NULL);
        lv_obj_add_event_cb(well, well_deleted, LV_EVENT_DELETE, NULL);
    }

    /* EEZ Studio variables (Variables panel). If these lines don't compile, the project needs a Build. */
    float left = eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_GAME_STEER_LEFT).toFloat();
    float right = eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_GAME_STEER_RIGHT).toFloat();
    float pedal = eez::flow::getGlobalVariable(FLOW_GLOBAL_VARIABLE_GAME_PEDAL_PCT).toFloat();

    float steer = (left != right) ? ((float)get_var_vcu_sagl() - left) / (right - left) : 0.5f;
    bool brake = ps_pedal_down(game.brake_was_down, (float)get_var_vcu_bps(), pedal);
    bool throttle = ps_pedal_down(throttle_was_down, (float)get_var_vcu_apps(), pedal);
    throttle_was_down = throttle;

    ps_step(&game, HAL_GetTick(), steer, brake, throttle);
    if (game.changed)
    {
        game.changed = false;
        lv_obj_invalidate(well);
    }
}

/* ---- the Game screen's variables (EEZ Studio: game_rows, game_best, game_text) ---- */

extern "C" int32_t get_var_game_rows(void) { return (int32_t)game.rows; }
extern "C" void set_var_game_rows(int32_t value) { (void)value; }

extern "C" int32_t get_var_game_best(void) { return (int32_t)game.best; }
extern "C" void set_var_game_best(int32_t value) { (void)value; }

extern "C" const char *get_var_game_text(void)
{
    switch (game.state)
    {
    case PS_READY:  return "BRAKE\nTO START";
    case PS_PAUSED: return "PAUSED\nBRAKE TO GO ON";
    case PS_OVER:   return "GAME OVER\nBRAKE TO RESTART";
    default:        return "";
    }
}
extern "C" void set_var_game_text(const char *value) { (void)value; }
