#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

/* Prototüübid */
static lv_disp_t * hal_init(int32_t w, int32_t h);
static void button_event_cb(lv_event_t * e);

/* Globaalne labeli viide */
static lv_obj_t * label;

/* Main */
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    lv_init();
    hal_init(1480, 320);

    /* Loo nupp */
    lv_obj_t * btn = lv_btn_create(lv_scr_act());
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, button_event_cb, LV_EVENT_CLICKED, NULL);

    /* Loo silt */
    label = lv_label_create(btn);
    lv_label_set_text(label, "Tere, maailm!");
    lv_obj_center(label);

    while (1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

/* Nupu callback */
static void button_event_cb(lv_event_t * e)
{
    lv_label_set_text(label, "Nuppu vajutati!");
}

/* HAL init */
static lv_disp_t * hal_init(int32_t w, int32_t h)
{
    lv_group_set_default(lv_group_create());

    lv_disp_t * disp = lv_sdl_window_create(w, h);

    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, disp);
    lv_disp_set_default(disp);

    LV_IMAGE_DECLARE(mouse_cursor_icon);
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act());
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse, cursor_obj);

    lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mousewheel, disp);
    lv_indev_set_group(mousewheel, lv_group_get_default());

    lv_indev_t * kb = lv_sdl_keyboard_create();
    lv_indev_set_display(kb, disp);
    lv_indev_set_group(kb, lv_group_get_default());

    return disp;
}
