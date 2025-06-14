#include "Global.h"
#include "RenderWindow.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include <stdio.h>

int Init();
void End();
void GameLoop();
void ProcessEvents();
void Display();

RenderWindow Window;
int isRunning = 1;

int main(int argc, char *argv[]) {

  if (!Init())
    return -1;
  GameLoop();
  End();
  return 0;
}

int Init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("ERROR::Could Not Init SDL:: %s\n", SDL_GetError());
    return 0;
  }
  printf("SDL app started succesfully\n");
  Window = CreateWindow("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
  if (Window.window == NULL || Window.renderer == NULL)
    isRunning = 0;
  return 1;
}

void End() {
  SDL_Quit();
  printf("Exiting SDL app\n");
}

void GameLoop() {
  while (isRunning == 1) {
    ProcessEvents();
    // Logica del juego
    Display();
  }
}

void Display() {
  ClearWindow(&Window);
  // Logica de renderizado
  DisplayWindow(&Window);
}

void ProcessEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_EVENT_QUIT:
      isRunning = 0;
      break;
    case SDL_EVENT_KEY_DOWN:
      if (e.key.key == SDLK_ESCAPE)
        isRunning = 0;
      break;
    }
  }
}
