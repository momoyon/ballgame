#ifndef CONTROL_NOB_H_
#define CONTROL_NOB_H_

#include "raylib.h"

typedef struct Control_nob {
  Vector2 pos;
  Vector2 vel;
  Vector2 acc;
  Color color;
  float radius;
  float speed;
} Control_nob;

Control_nob make_control_nob(Vector2 pos, float radius, Color color);
void update_control_nob(Control_nob *nob, float dt);
void draw_control_nob(Control_nob *nob);
void control_da_control_nob(Control_nob *nob, int upkey, int downkey);

#endif // !CONTROL_NOB_H_
