#include "RenderWindow.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

RenderWindow CreateWindow(const char *title, int w, int h) {
  RenderWindow Window = {NULL, NULL};
  Window.window = SDL_CreateWindow(title, w, h, 0);
  if (Window.window == NULL) {
    printf("ERROR:: Could not create SDL Window :: %s \n", SDL_GetError());
  }
  Window.renderer = SDL_CreateRenderer(Window.window, NULL);
  if (Window.renderer == NULL) {
    printf("ERROR:: Could not create SDL Renderer :: %s \n", SDL_GetError());
  }
  return Window;
}

void ClearWindow(RenderWindow *Window) {
  SDL_SetRenderDrawColor(Window->renderer, 100, 151, 177, 255);
  SDL_RenderClear(Window->renderer);
}

void DisplayWindow(RenderWindow *Window) {
  SDL_RenderPresent(Window->renderer);
}

void CleanUpWindow(RenderWindow *Window) {
  if (Window->renderer != NULL)
    SDL_DestroyRenderer(Window->renderer);
  if (Window->window != NULL)
    SDL_DestroyWindow(Window->window);
  Window->window = NULL;
  Window->renderer = NULL;
}
