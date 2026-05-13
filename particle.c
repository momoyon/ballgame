#include <particle.h>
#include <raylib.h>

Particle make_particle(Vector2 pos, float radius, Color color, float lifetime) {
  Particle res = {0};
  res.pos = pos;
  res.radius = radius;
  res.color = color;
  res.lifetime = lifetime > 0 ? lifetime : 0.1f;
  res.vel = v2_scale(v2_from_degrees(randomf(0, 360)), randomf(1.f, 100.f));

  return res;
}

void update_particle(Particle *p, float dt) {
  p->vel = v2_add(p->vel, p->acc);
  p->pos = v2_add(p->pos, v2_scale(p->vel, dt));
  p->acc = v2xx(0);

  p->time += dt;
}

void draw_particle(Particle *p) {
  DrawCircleV(p->pos, p->radius, ColorAlpha(p->color, (p->lifetime - p->time) / p->lifetime));
}
