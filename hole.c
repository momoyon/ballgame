#include <hole.h>

void draw_hole(Hole *h) {
  DrawCircleV(h->pos, h->radius, BLACK);
  DrawCircleLinesV(h->pos, h->radius, WHITE);
}

