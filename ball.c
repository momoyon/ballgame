#include "raylib.h"
#include <ball.h>

#include <engine.h> 

Ball make_ball(Vector2 pos, float radius, Color color) {
  Ball res = {
    .pos = pos,
    .vel = v2xx(0),
    .acc = v2xx(0),
    .radius = radius,
    .color = color,
  };

  return res;
}

void update_ball(Ball *b, float dt) {
  b->vel = v2_add(b->vel, b->acc);
  b->pos = v2_add(b->pos, v2_scale(b->vel, dt));
  b->acc = v2xx(0);
}

void draw_ball(Ball *b) {
  DrawCircleV(b->pos, b->radius, b->color);
}
