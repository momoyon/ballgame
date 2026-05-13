#include "config.h"
#include "packed_include.h"
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

  if (load_texture_from_data(&g_asset_manager, "ball.png", BALL_PNG_DATA,
                             BALL_PNG_DATA_SIZE, &res.tex)) {
    ASSERT(init_sprite(&res.spr, res.tex, 1, 1),
           "ball sprite initializaiton fail");
    center_sprite_origin(&res.spr);
  }

  return res;
}

void update_ball(Ball *b, float dt) {
  if (IsTextureValid(b->tex)) {
    b->spr.pos = b->pos;
    b->spr.rotation += b->rot_vel;
    set_sprite_scale_scalar(&b->spr, b->radius / b->og_radius);
  }

  switch (b->state) {
  case BALL_STATE_NORMAL: {
    b->vel = v2_add(b->vel, b->acc);
    b->pos = v2_add(b->pos, v2_scale(b->vel, dt));
    b->acc = v2xx(0);
    b->rot_vel = b->vel.x * 0.1;
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

void draw_ball(Ball *b) {
  if (IsTextureValid(b->tex)) {
    draw_sprite(&b->spr);
  } else {
    DrawCircleV(b->pos, b->radius, b->color);
  }
}
