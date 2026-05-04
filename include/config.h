#ifndef CONFIG_H_
#define CONFIG_H_

#include <engine.h>

extern int g_screen_width;
extern int g_screen_height;

extern int g_width;
extern int g_height;

extern float g_control_nob_speed;
extern float g_gravity;

extern Asset_manager g_asset_manager;

#define BACKGROUND_COLOR CLITERAL(Color){0x22, 0x20, 0x34, 0xFF}

#endif // !CONFIG_H_
