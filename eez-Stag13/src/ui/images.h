#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_stag;
extern const lv_img_dsc_t img_sponsor_uos;
extern const lv_img_dsc_t img_sponsor_sfs;
extern const lv_img_dsc_t img_sponsor_vector;
extern const lv_img_dsc_t img_sponsor_rfpro;
extern const lv_img_dsc_t img_sponsor_about_energy;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[6];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/