#include "fire.h"
#include <string>

void fire::lcd::initialize() {
    // Get the screen
    lv_obj_t *screen = lv_disp_get_scr_act(NULL);

    // make the screen unscrollable
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);


    // create the console
    console = lv_obj_create(screen);

    // style the console
    lv_obj_set_style_radius(console, 0, 0);
    lv_obj_set_style_bg_color(console, lv_color_black(), 0);

    // change its position to the corner
    lv_obj_set_pos(console, -2, -2);

    // make it cover the whole screen
    lv_obj_set_size(console, 484, 244);

    // make the console unscrollable
    lv_obj_set_scrollbar_mode(console, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(console, LV_OBJ_FLAG_SCROLLABLE);


    // create the console text
    console_text = lv_label_create(console);

    // make the console text unscrollable
    lv_obj_set_scrollbar_mode(console_text, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(console_text, LV_OBJ_FLAG_SCROLLABLE);

    // set the text color
    lv_obj_set_style_text_color(console_text, lv_color_white(), 0);

    // position the console text
    lv_obj_set_pos(console_text, -10, -10);

    std::string full_console = "";

    for (int i = 0; i < 14; i++) {
        full_console.append(display[i] + "\n");
    }

    // set the console text
    lv_label_set_text(console_text, full_console.c_str());


    // allow lcd functions
    initialized = true;
}

void fire::lcd::print(std::string str) {
    // exit if pros not initialized
    if (!fire::lcd::initialized) {return;}

    // find empty strings
    for (int i = 0; i < 14; i++) {
        if (display[i] == "") {
            // set spot to string
            display[i] = str;
            // update display
            std::string full_console = "";

            // loop lines and add them to the console
            for (int j = 0; j < 14; j++) {
                full_console.append(display[j] + "\n");
            }

            lv_label_set_text(console_text, full_console.c_str());

            // leave print
            return;
        }
    }
    // continue if no empty lines

    // shift all lines
    for (int i = 1; i < 14; i++) {
        display[i-1] = display[i];
    }
    // update last line
    display[13] = str;

    // update display
    std::string full_console = "";

    // loop lines and add them to the console
    for (int j = 0; j < 14; j++) {
        full_console.append(display[j] + "\n");
    }

    lv_label_set_text(console_text, full_console.c_str());
}
void fire::lcd::println(int line, std::string str) {
    // exit if pros not initialized
    if (!fire::lcd::initialized) {return;}

    // update line
    display[line] = str;

    // update display
    std::string full_console = "";

    // loop lines and add them to the console
    for (int j = 0; j < 14; j++) {
        full_console.append(display[j] + "\n");
    }

    lv_label_set_text(console_text, full_console.c_str());
}

void fire::lcd::clear() {
    for (int i = 0; i < 14; i++) {
        display[i] = "";
    }
    lv_label_set_text(console_text, "");
}