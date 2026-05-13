#include "ball.h"
#include "config.h"
#include "particle.h"
#include <common.h>

void add_particles(Vector2 pos, int count) {
  for (int i = 0; i < count; ++i) {
    Particle p = make_particle(pos, randomf(1.f, 5.f), WHITE,
                               randomf(0.1f, 1.f));
    darr_append(g_particles, p);
  }
}

bool init_sprite_scaled(Sprite *spr, Texture2D tex, size_t hframes, size_t vframes) {
  if (!init_sprite(spr, tex, hframes, vframes)) return false;
  set_sprite_scale_scalar(spr, __screen_scale);

  return true;
}
