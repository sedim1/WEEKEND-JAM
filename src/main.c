#include "Global.h"
#include "Mouse.h"
#include "Player.h"
#include "RenderWindow.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_timer.h"
#include "Sprite.h"
#include <stdio.h>

int Init();
void End();
void GameLoop();
void Update(float dt);
void ProcessEvents();
void Display();

RenderWindow Window;
int isRunning = 1;

Mouse mouse;

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
  StartPlayer(&Window);
  return 1;
}

void End() {
  EndPlayer();
  SDL_Quit();
  printf("Exiting SDL app\n");
}

void GameLoop() {
  float deltaTime = 0.0f, lastTime = 0.0f;
  while (isRunning == 1) {
    float currentTime = (float)SDL_GetTicks() / 1000.0f;
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    ProcessEvents();
    Update(deltaTime);
    // Logica del juego
    Display();
  }
}

void Update(float dt) { FollowMouse(mouse.posX, mouse.posY, dt); }

void Display() {
  ClearWindow(&Window);
  // Logica de renderizado
  DrawPlayer(&Window);
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
    case SDL_EVENT_MOUSE_MOTION:
      mouse.posX = e.motion.x;
      mouse.posY = e.motion.y;
      mouse.relX = e.motion.xrel;
      mouse.relY = e.motion.yrel;
      break;
    default:
      break;
    }
  }
}
