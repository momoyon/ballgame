#include "ball.h"
#include "raylib.h"
#include <state.h>
#include <control_nob.h>
#include <asset_packer.h>

#include <packed/title_screen.png.h>

#include <config.h>
#define ENGINE_IMPLEMENTATION
#include <engine.h>

#define COMMONLIB_REMOVE_PREFIX
#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

#define control_radius 16.f
Color control_color = { 255, 0, 0, 0 };
float pad = control_radius * 2.f;

float dt = 0;
const int substeps = 2;

Control_nob left;
Control_nob right;
Ball ball;

State current_state = STATE_MENU;

// state machine
const char* menuitems[] = {
    "Start Game",
    "Options",
    "Exit",
};
int selected_menu_item = 0;

void play_update(float dt);

static void reset(void) {
  left = make_control_nob(v2(pad, g_height - pad), control_radius, RED);
  right =
      make_control_nob(v2(g_width - pad, g_height - pad), control_radius, BLUE);

  ball = make_ball(v2(g_width * 0.5, g_height * 0.5), control_radius, YELLOW);

  current_state = STATE_MENU;
}

int main(void) {
  init_window(g_screen_width, g_screen_height, 1.0, "Ball Game", &g_width,
              &g_height);
  SetTargetFPS(60);

  reset();

  Texture2D title_screen_tex = { 0 };
  if (!load_texture_from_data(&g_asset_manager, "title_screen.png", TITLE_SCREEN_PNG_DATA, TITLE_SCREEN_PNG_DATA_SIZE, &title_screen_tex)) { return 1; }

  while (!WindowShouldClose()) {
    dt = GetFrameTime();
    begin_frame();

    // input
    switch (current_state) {
        case STATE_MENU: {
            if (IsKeyPressed(KEY_DOWN)) {
                selected_menu_item = (selected_menu_item + 1) % (sizeof(menuitems) / sizeof(menuitems[0]));
			}
            if (IsKeyPressed(KEY_UP)) {
                selected_menu_item = (selected_menu_item - 1 + (sizeof(menuitems) / sizeof(menuitems[0]))) % (sizeof(menuitems) / sizeof(menuitems[0]));

            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (selected_menu_item == 0) {
                    current_state = STATE_PLAYING;
                }
                else if (selected_menu_item == 1) {
                    ASSERT(false, "Options not implemented yet!");
                }
                else if (selected_menu_item == 2) {
                    close_window();
                    return 0;
                }
            }
        } break;
        case STATE_PLAYING: {
            control_da_control_nob(&left, KEY_S, KEY_C);
            control_da_control_nob(&right, KEY_K, KEY_N);
        } break;
        case STATE_GAMEOVER: {
            if (IsKeyPressed(KEY_SPACE)) {
                reset();
                current_state = STATE_PLAYING;
            }
        } break;
        default: {
            ASSERT(false, "UNREACHABLE!");
        }
    }

    // update
    switch (current_state) {
        case STATE_MENU: {
        } break;
        case STATE_PLAYING: {
            play_update(dt);
        } break;
        case STATE_GAMEOVER: {
        
        } break;
        default: {
            ASSERT(false, "UNREACHABLE!");
        }
    }

    // draw
    ClearBackground(BLACK);

    if (current_state != STATE_MENU) {
        draw_control_nob(&left);
        draw_control_nob(&right);
        // draw line
        DrawLineV(v2(left.pos.x, left.pos.y - left.radius),
            v2(right.pos.x, right.pos.y - right.radius), WHITE);
        draw_ball(&ball);
    }

    switch (current_state) {
        case STATE_MENU: {
			DrawTextureV(title_screen_tex, v2(0, 0), WHITE);
            for (int i = 0; i < sizeof(menuitems) / sizeof(menuitems[0]); ++i) {
                draw_text_aligned(GetFontDefault(), menuitems[i],
                    v2(g_width * 0.5, g_height * 0.5 + i * 30), 20 + (i == selected_menu_item ? 10 : 0),
                    TEXT_ALIGN_V_CENTER, TEXT_ALIGN_H_CENTER,
                    i == selected_menu_item ? YELLOW : WHITE);
			}
        } break;
        case STATE_PLAYING: {
        } break;
        case STATE_GAMEOVER: {
            draw_text_aligned(GetFontDefault(), "Game Over!",
                v2(g_width * 0.5, g_height * 0.5), 20, TEXT_ALIGN_V_CENTER, TEXT_ALIGN_H_CENTER, WHITE);
        } break;
        default: {
            ASSERT(false, "UNREACHABLE!");
        }
    }

    // debug
    //Vector2 mid = v2_add(p1, v2_scale(line, 0.5));
    //DrawCircleV(mid, 8, GOLD);
    //DrawLineV(mid, v2_add(mid, v2_scale(normal_to_line, 100)), WHITE);

    end_frame();
  }

  clean_asset_manager(&g_asset_manager);
  close_window();

  return 0;
}


void play_update(float dt) {
    Vector2 line = { 0 };
    Vector2 normal_to_line = { 0 };
    Vector2 p1 = v2_sub(left.pos, v2(0, left.radius));
    Vector2 p2 = v2_sub(right.pos, v2(0, right.radius));
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
        }
        else if (ball_x >= p2.x) {
            line_y_at_ball = p2.y; // Right of right nob: use right endpoint y
        }
        else {
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
            current_state = STATE_GAMEOVER;
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
