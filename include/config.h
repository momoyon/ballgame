#ifndef CONFIG_H_
#define CONFIG_H_

#include <engine.h>

typedef struct Key_config {
  int key_confirm;
  int key_left_up;
  int key_left_down;
  int key_right_up;
  int key_right_down;
  int key_slow_down;
} Key_config;

extern int g_screen_width;
extern int g_screen_height;

extern int g_width;
extern int g_height;

extern float g_control_nob_speed;
extern float g_gravity;

extern Key_config key_config;

extern Asset_manager g_asset_manager;

#define BACKGROUND_COLOR CLITERAL(Color){0x22, 0x20, 0x34, 0xFF}

#endif // !CONFIG_H_
