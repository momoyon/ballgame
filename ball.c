#include "raylib.h"
#include <ball.h>

#include <engine.h>

Ball make_ball(Vector2 pos, float radius, Color color) {
  Ball res = {
      .pos = pos,
      .vel = v2xx(0),
      .acc = v2xx(0),
      .radius = radius,
      .og_radius = radius,
      .color = color,
  };

  return res;
}

void update_ball(Ball *b, float dt) {
  switch (b->state) {
  case BALL_STATE_NORMAL: {
    b->vel = v2_add(b->vel, b->acc);
    b->pos = v2_add(b->pos, v2_scale(b->vel, dt));
    b->acc = v2xx(0);
  } break;
  case BALL_STATE_SUCKING: {
    b->radius -= 100 * dt;

    if (b->radius <= 0.f) {
      b->state = BALL_STATE_SUCKED;
    }
  } break;
  case BALL_STATE_SUCKED: {
    b->state = BALL_STATE_NORMAL;
  } break;
  default:
    ASSERT(false, "UNREACHABLE!");
  }
}

void draw_ball(Ball *b) { DrawCircleV(b->pos, b->radius, b->color); }
