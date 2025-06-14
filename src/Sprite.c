#include "Sprite.h"
#include "Global.h"
#include "RenderWindow.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include <stdio.h>

Sprite NewSprite(RenderWindow *window, const char *path, int w, int h) {
  Sprite sprite = {NULL, w, h, 0, 0, 0.0, 0.0, 1};
  sprite.texture = IMG_LoadTexture(window->renderer, path);
  if (sprite.texture == NULL)
    printf("ERROR::Could not load %s\n", path);
  else {
    printf("Texture %s was succesfully loaded\n", path);
    SDL_SetTextureScaleMode(sprite.texture, SDL_SCALEMODE_NEAREST);
  }
  return sprite;
}
void FreeSprite(Sprite *sprite) {
  if (sprite->texture != NULL)
    SDL_DestroyTexture(sprite->texture);
  sprite->texture = NULL;
  sprite->posX = sprite->posY = 0.0f;
  sprite->width = sprite->height = 0;
  sprite->size = 0;
}

void DrawCoverSprite(RenderWindow *window, Sprite *sprite) {
  SDL_RenderTexture(window->renderer, sprite->texture, NULL, NULL);
}

void DrawSprite(RenderWindow *window, Sprite *sprite) {
  SDL_FRect src = {(int)sprite->width * sprite->atlasX,
                   (int)sprite->height * sprite->atlasY, (float)sprite->width,
                   (float)sprite->height};
  SDL_FRect dest = {sprite->posX, sprite->posY,
                    (float)sprite->width * sprite->size * SPRITE_SCALE,
                    (float)sprite->height * sprite->size * SPRITE_SCALE};
  SDL_RenderTexture(window->renderer, sprite->texture, &src, &dest);
}
