#include <config.h>

int g_screen_width  = 800;
int g_screen_height = 600;

int g_width  = 0;
int g_height = 0;

float g_control_nob_speed = 100.f;
float g_gravity = 9.8;

Key_config key_config = {
  .key_confirm = KEY_SPACE,
  .key_left_down = KEY_C,
  .key_left_up = KEY_S,
  .key_right_down = KEY_N,
  .key_right_up = KEY_K,
  .key_slow_down = KEY_LEFT_SHIFT,
};

Asset_manager g_asset_manager = { 0 };
