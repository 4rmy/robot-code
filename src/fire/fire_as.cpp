#include "fire.h"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/misc/lv_color.h"
#include "liblvgl/misc/lv_style.h"
#include "liblvgl/misc/lv_txt.h"
#include "liblvgl/widgets/lv_btn.h"
#include "liblvgl/widgets/lv_label.h"
#include <string>

void fire::as::next_handle(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    fire::as::page_up();
  }
}
void fire::as::prev_handle(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    fire::as::page_down();
  }
}
void fire::as::select_handle(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    if (lv_event_get_target(e) == Auton1) {
      if (current_page*5 < autons.size()) {
        index = current_page*5;
        lv_label_set_text(selected, ("Selected:\n" + autons[current_page*5].name).c_str());
        lv_obj_set_style_bg_color(Auton1, lv_color_hex(0x0000FF), 0);
        lv_obj_set_style_border_color(Auton1, lv_color_hex(0x0000AA), 0);

        lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);
      }
    } else if (lv_event_get_target(e) == Auton2) {
      if (current_page*5 + 1 < autons.size()) {
        index = current_page*5 + 1;
        lv_label_set_text(selected, ("Selected:\n" + autons[current_page*5 + 1].name).c_str());
        lv_obj_set_style_bg_color(Auton2, lv_color_hex(0x0000FF), 0);
        lv_obj_set_style_border_color(Auton2, lv_color_hex(0x0000AA), 0);

        lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);
      }
    } else if (lv_event_get_target(e) == Auton3) {
      if (current_page*5 + 2 < autons.size()) {
        index = current_page*5 + 2;
        lv_label_set_text(selected, ("Selected:\n" + autons[current_page*5 + 2].name).c_str());
        lv_obj_set_style_bg_color(Auton3, lv_color_hex(0x0000FF), 0);
        lv_obj_set_style_border_color(Auton3, lv_color_hex(0x0000AA), 0);

        lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);
      }
    } else if (lv_event_get_target(e) == Auton4) {
      if (current_page*5 + 3 < autons.size()) {
        index = current_page*5 + 3;
        lv_label_set_text(selected, ("Selected:\n" + autons[current_page*5 + 3].name).c_str());
        lv_obj_set_style_bg_color(Auton4, lv_color_hex(0x0000FF), 0);
        lv_obj_set_style_border_color(Auton4, lv_color_hex(0x0000AA), 0);

        lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);
      }
    } else if (lv_event_get_target(e) == Auton5) {
      if (current_page*5 + 4 < autons.size()) {
        index = current_page*5 + 4;
        lv_label_set_text(selected, ("Selected:\n" + autons[current_page*5 + 4].name).c_str());
        lv_obj_set_style_bg_color(Auton5, lv_color_hex(0x0000FF), 0);
        lv_obj_set_style_border_color(Auton5, lv_color_hex(0x0000AA), 0);

        lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
        
        lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
        lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
      }
    }
  }
}

void fire::as::add_autons(std::vector<Auton> auton_list) {
  autons = auton_list;
}

void fire::as::init_selector() {
  screen = lv_obj_create(lv_scr_act());
  lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_radius(screen, 0, 0);
  lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

  // make it cover the whole screen
  lv_obj_set_pos(screen, -2, -2);
  lv_obj_set_size(screen, 484, 244);

  // add previous and next buttons
  lv_obj_t *prev = lv_btn_create(screen);
  lv_obj_set_pos(prev, 0, 150);
  lv_obj_set_size(prev, 121, 61);
  lv_obj_add_event_cb(prev, prev_handle, LV_EVENT_CLICKED, NULL);

  lv_obj_t *prev_text = lv_label_create(prev);
  lv_label_set_text(prev_text, "Previous\nPage");
  lv_obj_set_size(prev_text, 121, 61);
  lv_obj_set_pos(prev_text, -20, 0);

  // add previous and next buttons
  lv_obj_t *next = lv_btn_create(screen);
  lv_obj_set_pos(next, 320, 150);
  lv_obj_set_size(next, 121, 61);
  lv_obj_add_event_cb(next, next_handle, LV_EVENT_CLICKED, NULL);

  lv_obj_t *next_text = lv_label_create(next);
  lv_label_set_text(next_text, "Next\nPage");
  lv_obj_set_size(next_text, 121, 61);
  lv_obj_set_pos(next_text, -20, 0);

  // style both buttons
  lv_obj_set_style_bg_color(prev, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_bg_color(next, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(prev, 4, 0);
  lv_obj_set_style_border_width(next, 4, 0);
  lv_obj_set_style_border_color(prev, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_border_color(next, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_text_align(prev_text, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_align(next_text, LV_TEXT_ALIGN_CENTER, 0);

  // page number display
  lv_obj_t *page_num_body = lv_obj_create(screen);
  lv_obj_set_style_bg_color(page_num_body, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(page_num_body, 4, 0);
  lv_obj_set_style_border_color(page_num_body, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(page_num_body, 160, 150);
  lv_obj_set_size(page_num_body, 121, 61);
  lv_obj_set_style_text_color(page_num_body, lv_color_white(), 0);

  page_limit = autons.size() / 5;

  page_num = lv_label_create(page_num_body);
  lv_label_set_text(page_num, ("Page: " + std::to_string(current_page + 1) + " / " + std::to_string(page_limit + 1)).c_str());

  // Auton Butons
  Auton1 = lv_btn_create(screen);
  lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(Auton1, 4, 0);
  lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(Auton1, 0, 0);
  lv_obj_set_size(Auton1, 121, 61);
  lv_obj_add_event_cb(Auton1, select_handle, LV_EVENT_CLICKED, NULL);
  lv_obj_set_scrollbar_mode(Auton1, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(Auton1, LV_OBJ_FLAG_SCROLLABLE);

  Auton2 = lv_btn_create(screen);
  lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(Auton2, 4, 0);
  lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(Auton2, 160, 0);
  lv_obj_set_size(Auton2, 121, 61);
  lv_obj_add_event_cb(Auton2, select_handle, LV_EVENT_CLICKED, NULL);
  lv_obj_set_scrollbar_mode(Auton2, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(Auton2, LV_OBJ_FLAG_SCROLLABLE);

  Auton3 = lv_btn_create(screen);
  lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(Auton3, 4, 0);
  lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(Auton3, 320, 0);
  lv_obj_set_size(Auton3, 121, 61);
  lv_obj_add_event_cb(Auton3, select_handle, LV_EVENT_CLICKED, NULL);
  lv_obj_set_scrollbar_mode(Auton3, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(Auton3, LV_OBJ_FLAG_SCROLLABLE);

  Auton4 = lv_btn_create(screen);
  lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(Auton4, 4, 0);
  lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(Auton4, 0, 75);
  lv_obj_set_size(Auton4, 121, 61);
  lv_obj_add_event_cb(Auton4, select_handle, LV_EVENT_CLICKED, NULL);
  lv_obj_set_scrollbar_mode(Auton4, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(Auton4, LV_OBJ_FLAG_SCROLLABLE);

  Auton5 = lv_btn_create(screen);
  lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(Auton5, 4, 0);
  lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(Auton5, 320, 75);
  lv_obj_set_size(Auton5, 121, 61);
  lv_obj_add_event_cb(Auton5, select_handle, LV_EVENT_CLICKED, NULL);
  lv_obj_set_scrollbar_mode(Auton5, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(Auton5, LV_OBJ_FLAG_SCROLLABLE);

  a1_text = lv_label_create(Auton1);
  lv_label_set_text(a1_text, "");
  a2_text = lv_label_create(Auton2);
  lv_label_set_text(a2_text, "");
  a3_text = lv_label_create(Auton3);
  lv_label_set_text(a3_text, "");
  a4_text = lv_label_create(Auton4);
  lv_label_set_text(a4_text, "");
  a5_text = lv_label_create(Auton5);
  lv_label_set_text(a5_text, "");

  // Selected Auton
  lv_obj_t *selected_body = lv_obj_create(screen);
  lv_obj_set_style_bg_color(selected_body, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_width(selected_body, 4, 0);
  lv_obj_set_style_border_color(selected_body, lv_color_hex(0xAA0000), 0);
  lv_obj_set_pos(selected_body, 160, 75);
  lv_obj_set_size(selected_body, 121, 61);
  lv_obj_set_style_text_color(selected_body, lv_color_white(), 0);
  lv_obj_set_scrollbar_mode(selected_body, LV_SCROLLBAR_MODE_OFF);
  lv_obj_clear_flag(selected_body, LV_OBJ_FLAG_SCROLLABLE);

  selected = lv_label_create(selected_body);
  lv_label_set_text(selected, "Selected:\nNone");
  lv_obj_set_pos(selected, -10, -10);
  lv_obj_set_size(selected, 121, 61);
  

  for (int i = 0; i < 5; i++) {
    if (current_page * 5 + i >= autons.size()) {
      break;
    }
    if (i == 0) {
      lv_label_set_text(a1_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 1) {
      lv_label_set_text(a2_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 2) {
      lv_label_set_text(a3_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 3) {
      lv_label_set_text(a4_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 4) {
      lv_label_set_text(a5_text, autons[current_page * 5 + i].name.c_str());
    }
  }

  // hide screen
  // for later
  // lv_obj_set_style_opa(screen, 100, 0);
}

void fire::as::page_up() {
  current_page++;
  if (current_page > page_limit) {
    current_page = page_limit;
  }
  lv_label_set_text(a1_text, "");
  lv_label_set_text(a2_text, "");
  lv_label_set_text(a3_text, "");
  lv_label_set_text(a4_text, "");
  lv_label_set_text(a5_text, "");
  for (int i = 0; i < 5; i++) {
    if (current_page * 5 + i >= autons.size()) {
      break;
    }
    if (i == 0) {
      lv_label_set_text(a1_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 1) {
      lv_label_set_text(a2_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 2) {
      lv_label_set_text(a3_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 3) {
      lv_label_set_text(a4_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 4) {
      lv_label_set_text(a5_text, autons[current_page * 5 + i].name.c_str());
    }
  }
  lv_label_set_text(page_num, ("Page: " + std::to_string(current_page + 1) + " / " + std::to_string(page_limit + 1)).c_str());

  lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);

  if (index == current_page*5){
    lv_obj_set_style_bg_color(Auton1, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton1, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 1){
    lv_obj_set_style_bg_color(Auton2, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton2, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 2){
    lv_obj_set_style_bg_color(Auton3, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton3, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 3){
    lv_obj_set_style_bg_color(Auton4, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton4, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 4){
    lv_obj_set_style_bg_color(Auton5, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton5, lv_color_hex(0x0000AA), 0);
  }
}

void fire::as::page_down() {
  current_page--;
  if (current_page < 0) {
    current_page = 0;
  }
  lv_label_set_text(a1_text, "");
  lv_label_set_text(a2_text, "");
  lv_label_set_text(a3_text, "");
  lv_label_set_text(a4_text, "");
  lv_label_set_text(a5_text, "");
  for (int i = 0; i < 5; i++) {
    if (current_page * 5 + i >= autons.size()) {
      break;
    }
    if (i == 0) {
      lv_label_set_text(a1_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 1) {
      lv_label_set_text(a2_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 2) {
      lv_label_set_text(a3_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 3) {
      lv_label_set_text(a4_text, autons[current_page * 5 + i].name.c_str());
    } else if (i == 4) {
      lv_label_set_text(a5_text, autons[current_page * 5 + i].name.c_str());
    }
  }

  lv_label_set_text(page_num, ("Page: " + std::to_string(current_page + 1) + " / " + std::to_string(page_limit + 1)).c_str());

  lv_obj_set_style_bg_color(Auton1, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton1, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton2, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton2, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton3, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton3, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton4, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton4, lv_color_hex(0xAA0000), 0);
  lv_obj_set_style_bg_color(Auton5, lv_color_hex(0xFF0000), 0);
  lv_obj_set_style_border_color(Auton5, lv_color_hex(0xAA0000), 0);

  if (index == current_page*5){
    lv_obj_set_style_bg_color(Auton1, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton1, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 1){
    lv_obj_set_style_bg_color(Auton2, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton2, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 2){
    lv_obj_set_style_bg_color(Auton3, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton3, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 3){
    lv_obj_set_style_bg_color(Auton4, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton4, lv_color_hex(0x0000AA), 0);
  } else if (index == current_page*5 + 4){
    lv_obj_set_style_bg_color(Auton5, lv_color_hex(0x0000FF), 0);
    lv_obj_set_style_border_color(Auton5, lv_color_hex(0x0000AA), 0);
  }
}

void fire::as::call_selected_auton() {
  fire::lcd::clear();
  if (index != -1) {
    autons[index].func();
  }
}

void fire::as::set_visible(bool visible) {
  lv_obj_set_style_opa(screen, (visible) ? 1 : 0, 0);
}