#ifndef BALL_H_
#define BALL_H_

#include "raylib.h"

typedef struct Ball {
  Vector2 pos;
  Vector2 vel;
  Vector2 acc;
  float radius;
  Color color;
} Ball;

Ball make_ball(Vector2 pos, float radius, Color color);
void update_ball(Ball *b, float dt);
void draw_ball(Ball *b);

#endif // !BALL_H_
