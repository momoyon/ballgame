#ifndef HOLE_H_
#define HOLE_H_

#include "raylib.h"
#include <stddef.h>

typedef struct Hole {
  Vector2 pos;
  float radius;
  bool goal;
} Hole;

typedef struct Holes {
  Hole *items;
  size_t count;
  size_t capacity;
} Holes;

void draw_hole(Hole *h);

#endif // HOLE_H_
