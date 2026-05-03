#include "raylib.h"
#include <control_nob.h>
#include <engine.h>
#include <config.h>

Control_nob make_control_nob(Vector2 pos, float radius, Color color) {
  Control_nob res = {
    .pos = pos,
    .vel = v2xx(0),
    .acc = v2xx(0),
    .radius = radius,
    .color = color,
    .speed = g_control_nob_speed,
  };
  return res;
}

void update_control_nob(Control_nob *nob, float dt) {
  nob->vel = v2_add(nob->vel, nob->acc);
  nob->pos = v2_add(nob->pos, v2_scale(nob->vel, dt));
  nob->acc = v2xx(0);

  nob->vel = v2_scale(nob->vel, 0.9);
}

void draw_control_nob(Control_nob *nob) {
  DrawCircleV(nob->pos, nob->radius, nob->color);
}

void control_da_control_nob(Control_nob *nob, int upkey, int downkey) {
  Vector2 dir = {0};
  if (IsKeyDown(upkey)) {
    dir.y--;
  }
  if (IsKeyDown(downkey)) {
    dir.y++;
  }

  nob->acc.y += dir.y * nob->speed;
}
