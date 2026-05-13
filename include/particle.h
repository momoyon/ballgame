#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "engine.h"

typedef struct Particle {
  Vector2 pos, vel, acc;
  float radius;
  Color color;
  float lifetime, time;
} Particle;

Particle make_particle(Vector2 pos, float radius, Color color, float lifetime);
void update_particle(Particle *p, float dt);
void draw_particle(Particle *p);


typedef struct Particles {
  Particle *items;
  size_t count;
  size_t capacity;
} Particles;

#endif // !PARTICLE_H_
