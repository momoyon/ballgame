#ifndef BALL_H_
#define BALL_H_

#include "raylib.h"

typedef enum Ball_state {
  BALL_STATE_NORMAL,
  BALL_STATE_SUCKING,
  BALL_STATE_SUCKED,
} Ball_state;

typedef struct Ball {
  Vector2 pos;
  Vector2 vel;
  Vector2 acc;
  float radius, og_radius;
  Color color;
  Ball_state state;
  bool sucked_to_goal;
} Ball;

Ball make_ball(Vector2 pos, float radius, Color color);
void update_ball(Ball *b, float dt);
void draw_ball(Ball *b);

#endif // !BALL_H_
