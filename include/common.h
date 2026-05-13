#ifndef COMMON_H_
#define COMMON_H_

#include "engine.h"

void add_particles(Vector2 pos, int count);
bool init_sprite_scaled(Sprite *spr, Texture2D tex, size_t hframes, size_t vframes);

#endif // COMMON_H_

