#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16
#define _FUNCTION 17
#define _ARROWS 18

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  /* LOWER, */
  /* RAISE, */
  /* ADJUST, */
  /* BACKLIT, */
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______  KC_TRNS
#define KC_XXXXX  KC_NO
/* Qwerty */
#define KC_CTLESC CTL_T(KC_ESC)
#define KC_CTLQUT RCTL_T(KC_QUOT)
#define KC_LOWER  MO(_LOWER)
#define KC_RAISE  MO(_RAISE)
#define KC_FUNC   MO(_FUNCTION)
#define KC_GUIBSP LGUI_T(KC_BSPC)
/* Lower */
#define KC_GUIGRV LGUI(KC_GRV)
#define KC_TABP   LGUI(LALT(KC_LEFT))
#define KC_TABN   LGUI(LALT(KC_RIGHT))
#define KC_PND    LALT(KC_3)
#define KC_CTLGRV CTL_T(KC_GRV)
#define KC_DSKP   LCTL(KC_LEFT)
#define KC_DSKN   LCTL(KC_RIGHT)
#define KC_CTLMIN RCTL_T(KC_MINS)
#define KC_LOCK   LCTL(LGUI(KC_Q))
#define KC_MISNCT LCTL(KC_UP)
#define KC_APPWIN LCTL(KC_DOWN)
#define KC_GUILFT LGUI(KC_LEFT)
#define KC_GUIDWN LGUI(KC_DOWN)
#define KC_GUIUP  LGUI(KC_UP)
#define KC_GUIRGT LGUI(KC_RGHT)
/* Raise */
#define KC_CTLDOT RCTL_T(KC_DOT)
#define KC_ALTLFT LALT(KC_LEFT)
#define KC_ALTDWN LALT(KC_DOWN)
#define KC_ALTUP  LALT(KC_UP)
#define KC_ALTRGT LALT(KC_RGHT)
/* Function Layer */
#define KC_HYPRS  HYPR(KC_S)
#define KC_HYPRX  HYPR(KC_X)
#define KC_HYPRD  HYPR(KC_D)
#define KC_HYPRC  HYPR(KC_C)
#define KC_FORCQ  LGUI(LALT(KC_ESC))
#define KC_RST    RESET
#define KC_LRST   RGBRST
#define KC_LTOG   RGB_TOG
#define KC_LMOD   RGB_MOD
#define KC_LRMOD  RGB_RMOD
#define KC_RASLK  TO(_RAISE)
#define KC_LHUI   RGB_HUI
#define KC_LHUD   RGB_HUD
#define KC_LSAI   RGB_SAI
#define KC_LSAD   RGB_SAD
#define KC_LVAI   RGB_VAI
#define KC_LVAD   RGB_VAD
#define KC_ARROW  TG(_ARROWS)
#define KC_LPLN   RGB_MODE_PLAIN
/* Arrows */
#define KC_QWERTY TO(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CTLESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,CTLQUT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,SFTENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER,GUIBSP,      SPC, RAISE,  FUNC \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     GUIGRV,  MUTE,  VOLD,  VOLU,  TABP,  TABN,                    PND,  LCBR,  RCBR,  LBRC,  RBRC,  PLUS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  MRWD,  MPLY,  MFFD,  DSKP,  DSKN,                   LEFT,  DOWN,    UP, RIGHT,  UNDS,CTLMIN,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LOCK,  SLCK,  PAUS,MISNCT,APPWIN,                 GUILFT,GUIDWN, GUIUP,GUIRGT, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,      DEL, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       TILD,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,   EQL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CTLGRV,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,CTLDOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                 ALTLFT,ALTDWN, ALTUP,ALTRGT, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_FUNCTION] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
         F1,    F2,    F3,    F4,    F5,    F6,                     F7,    F8,    F9,   F10,   F11,   F12,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CTLESC, XXXXX, HYPRS, HYPRD, FORCQ,   RST,                   LMOD,  LHUI,  LSAI,  LVAI, ARROW,  RCTL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, HYPRX, HYPRC, XXXXX,  LRST,                  LRMOD,  LHUD,  LSAD,  LVAD,  LPLN,  CAPS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, XXXXX, _____,     LTOG, RASLK, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_ARROWS] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,  MUTE,  VOLD,  VOLU,  TABP,  TABN,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  MRWD,  MPLY,  MFFD,  DSKP,  DSKN,                   LEFT,  DOWN,    UP,  RGHT, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LOCK, XXXXX, XXXXX,MISNCT,APPWIN,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, ARROW, _____,    _____, ARROW, _____ \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
/* const char *read_keylogs(void); */

// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
  } else {
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_timelog());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    set_timelog();
  }
  switch (keycode) {
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
