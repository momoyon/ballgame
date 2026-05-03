#include "ball.h"
#include "raylib.h"
#include <control_nob.h>

#include <config.h>
#define ENGINE_IMPLEMENTATION
#include <engine.h>

#define COMMONLIB_REMOVE_PREFIX
#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

#define control_radius 16.f
Color control_color = RED;
float pad = control_radius * 2.f;

bool gameover = false;

void reset(Control_nob *l, Control_nob *r, Ball *b) {
  *l = make_control_nob(v2(pad, g_height - pad), control_radius, RED);
  *r =
      make_control_nob(v2(g_width - pad, g_height - pad), control_radius, BLUE);

  *b = make_ball(v2(g_width * 0.5, g_height * 0.5), control_radius, YELLOW);

  gameover = false;
}

int main(void) {
  init_window(g_screen_width, g_screen_height, 1.0, "Ball Game", &g_width,
              &g_height);
  SetTargetFPS(60);

  Control_nob left =
      make_control_nob(v2(pad, g_height - pad), control_radius, RED);
  Control_nob right =
      make_control_nob(v2(g_width - pad, g_height - pad), control_radius, BLUE);

  Ball ball =
      make_ball(v2(g_width * 0.5, g_height * 0.5), control_radius, YELLOW);

  float dt = 0;
  const int substeps = 2;

  while (!WindowShouldClose()) {
    dt = GetFrameTime();
    begin_frame();

    // input
    if (gameover) {
      if (IsKeyPressed(KEY_SPACE)) {
        reset(&left, &right, &ball);
      }
    } else {
      control_da_control_nob(&left, KEY_S, KEY_C);
      control_da_control_nob(&right, KEY_K, KEY_N);
    }

    // update
    Vector2 line;
    Vector2 normal_to_line;
    Vector2 p1 = v2_sub(left.pos, v2(0, left.radius));
    Vector2 p2 = v2_sub(right.pos, v2(0, right.radius));
    if (!gameover) {

      // apply gravity to ball
      ball.acc.y = g_gravity;
      update_ball(&ball, dt);
      for (int i = 0; i < substeps; ++i) {
        float subdt = dt / substeps;
        update_control_nob(&left, subdt);
        update_control_nob(&right, subdt);

        // collide ball with line
        if (CheckCollisionCircleLine(ball.pos, ball.radius, p1, p2)) {
          line = v2_sub(p2, p1);
          normal_to_line = v2_normalize(v2(line.y, -line.x));
          ball.acc = v2_add(ball.acc, v2_scale(normal_to_line, 10));
        }

        float line_y_at_ball = 0.0f;
        float ball_x = ball.pos.x;
        if (ball_x <= p1.x) {
          line_y_at_ball = p1.y; // Left of left nob: use left endpoint y
        } else if (ball_x >= p2.x) {
          line_y_at_ball = p2.y; // Right of right nob: use right endpoint y
        } else {
          // Linear interpolation between p1 and p2
          float t = (ball_x - p1.x) / (p2.x - p1.x);
          line_y_at_ball = p1.y + t * (p2.y - p1.y);
        }

        float ball_bottom = ball.pos.y + ball.radius;
        if (ball_bottom > line_y_at_ball) {
          // Move ball up so its bottom touches the line
          ball.pos.y = line_y_at_ball - ball.radius;
          // Stop downward velocity (use *= -0.9 for bounce instead of 0 if
          // desired)
          if (ball.vel.y > 0)
            ball.vel.y = 0;
        }

        if (ball.pos.x < left.pos.x || ball.pos.x > right.pos.x) {
          gameover = true;
        }
      }

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
    }

    // draw
    ClearBackground(BLACK);
    draw_control_nob(&left);
    draw_control_nob(&right);
    draw_ball(&ball);

    // draw line
    DrawLineV(v2(left.pos.x, left.pos.y - left.radius),
              v2(right.pos.x, right.pos.y - right.radius), WHITE);

    if (gameover) {
      draw_text(GetFontDefault(), "Game Over!",
                v2(g_width * 0.5, g_height * 0.5), 20, WHITE);
    }

    // debug
    Vector2 mid = v2_add(p1, v2_scale(line, 0.5));
    DrawCircleV(mid, 8, GOLD);
    DrawLineV(mid, v2_add(mid, v2_scale(normal_to_line, 100)), WHITE);

    end_frame();
  }
  close_window();

  return 0;
}
