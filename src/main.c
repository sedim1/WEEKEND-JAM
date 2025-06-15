#include "Cleanable.h"
#include "Global.h"
#include "Mouse.h"
#include "Number.h"
#include "Plates.h"
#include "Player.h"
#include "RenderWindow.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_timer.h"
#include "Sprite.h"
#include <stdio.h>
#include <time.h>

int Init();
void InitGame();
void End();
void GameLoop();
void Update(float dt);
void ProcessEvents();
void Display();

enum GameState {
  MAIN_MENU,
  PLAYING,
  RESULT_SCREEN,
};

RenderWindow Window;
int isRunning = 1;

Mouse mouse;
float lastRelX = 0.0f;
float lastRelY = 0.0f;
Plate plate;
Cleanables c;
Sprite Background;
TEXT_NUMBER countdown;
TEXT_NUMBER cleanedPlates;
enum GameState gameState = RESULT_SCREEN;

int main(int argc, char *argv[]) {

  if (!Init())
    return -1;
  GameLoop();
  End();
  return 0;
}

int Init() {
  srand(time(NULL));
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("ERROR::Could Not Init SDL:: %s\n", SDL_GetError());
    return 0;
  }
  printf("SDL app started succesfully\n");
  Window = CreateWindow("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
  if (Window.window == NULL || Window.renderer == NULL)
    isRunning = 0;
  plate = NewPlate(&Window);
  c = clenables(&Window);
  Background = NewSprite(&Window, "Assets/Textures/Background.png", 128, 112);
  countdown = textNumber(&Window);
  cleanedPlates = textNumber(&Window);
  countdown.value = 134;
  StartPlayer(&Window);
  ResetCleanable(&c);
  return 1;
}

void End() {
  FreeSprite(&Background);
  FreeSprite(&cleanedPlates.texture);
  FreeSprite(&countdown.texture);
  EndCleanables(&c);
  FreeSprite(&plate.sprite);
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

void Update(float dt) {
  if (gameState == MAIN_MENU) {
  }
  if (gameState == PLAYING) {
    FollowMouse(mouse.posX, mouse.posY, dt);
    PlateUpdate(&plate, &c, &mouse, dt);
  } else if (gameState == RESULT_SCREEN) {
  }
}

void Display() {
  ClearWindow(&Window);
  DrawCoverSprite(&Window, &Background);
  // Logica de renderizado

  if (gameState == MAIN_MENU) {
  } else if (gameState == PLAYING) {
    DrawPlate(&Window, &plate, &c);
    DrawPlayer(&Window);
    DrawTextNumber(&Window, &countdown, 0.0f, 0.0f);
  } else if (gameState == RESULT_SCREEN) {
    DrawTextNumber(&Window, &cleanedPlates, 0.0f, 0.0f);
  }

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
      if (mouse.relX == lastRelX && mouse.relY == lastRelY) {
        mouse.relX = 0.0f;
        mouse.relY = 0.0f;
      } else {
        lastRelX = mouse.relX;
        lastRelY = mouse.relY;
      }
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (e.button.button == SDL_BUTTON_LEFT)
        mouse.isPressed = 1;
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      if (e.button.button == SDL_BUTTON_LEFT)
        mouse.isPressed = 0;
      break;
    default:
      mouse.relX = 0.0f;
      mouse.relY = 0.0f;
      break;
    }
  }
}

void InitGame() {}
