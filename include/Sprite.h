#ifndef SPRITE_H
#define SPRITE_H

#include "RenderWindow.h"
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"

typedef struct {
  SDL_Texture *texture;
  int width;
  int height;
  float posX, posY;
  float size;
} Sprite;

Sprite NewSprite(RenderWindow *window, const char *path, int w, int h);
void FreeSprite(Sprite *sprite);
void DrawCoverSprite(RenderWindow *window, Sprite *sprite);
void DrawSprite(RenderWindow *window, Sprite *sprite);

#endif // !DEBUG
