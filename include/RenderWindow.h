#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <stdio.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} RenderWindow;

RenderWindow CreateWindow(const char *title, int w, int h);
void ClearWindow(RenderWindow *Window);
void DisplayWindow(RenderWindow *Window);
void CleanUpWindow(RenderWindow *Window);

#endif
