#include "raylib.h"
#include <control_nob.h>

#include <config.h>
#define ENGINE_IMPLEMENTATION
#include <engine.h>

#define COMMONLIB_REMOVE_PREFIX
#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

int main() {
  init_window(g_screen_width, g_screen_height, 1.0, "Ball Game", &g_width, &g_height);
  SetTargetFPS(60);

  float control_radius = 16.f;
  Color control_color = RED;

  float pad = control_radius * 2.f;
  Control_nob left = make_control_nob(v2(pad, g_height - pad), control_radius, RED);
  Control_nob right = make_control_nob(v2(g_width - pad, g_height - pad), control_radius, BLUE);

  float dt = 0;

  while (!WindowShouldClose()) {
    dt = GetFrameTime();
    begin_frame();


    // input
    control_da_control_nob(&left,  KEY_S, KEY_C);
    control_da_control_nob(&right, KEY_K, KEY_N);

    // update
    update_control_nob(&left, dt);
    update_control_nob(&right, dt);

    // bind nobs to the window
    if (left.pos.y < pad + left.radius) {
      left.pos.y = pad + left.radius;
    }
    if (left.pos.y > g_height - pad - left.radius) {
      left.pos.y = g_height - pad - left.radius;
    }
    if (right.pos.y < pad + right.radius) {
      right.pos.y = pad + right.radius;
    }
    if (right.pos.y > g_height - pad - right.radius) {
      right.pos.y = g_height - pad - right.radius;
    }

    // draw
    ClearBackground(BLACK);
    draw_control_nob(&left);
    draw_control_nob(&right);

    end_frame();
  }
  close_window();

  return 0;
}
