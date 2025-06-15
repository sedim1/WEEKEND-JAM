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
  PREPARING,
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
Sprite Background2;
Sprite Background3;
TEXT_NUMBER countdown;
TEXT_NUMBER cleanedPlates;
Sprite CleanedText;
enum GameState gameState = MAIN_MENU;
extern Player player;

float timerCurrentTime = 0.0f;
float timerLastTime = 0.0f;
int timerFinished = 0;

int gameStart = 0;

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
  Background2 =
      NewSprite(&Window, "Assets/Textures/BackgroundMain.png", 128, 112);
  Background3 =
      NewSprite(&Window, "Assets/Textures/BackgroundMain2.png", 128, 112);
  countdown = textNumber(&Window);
  CleanedText = NewSprite(&Window, "Assets/Textures/Cleaned.png", 126, 64);
  cleanedPlates = textNumber(&Window);
  CleanedText.posX = SCREEN_WIDTH / 4.0f - 150.0f;
  CleanedText.posY = SCREEN_HEIGHT / 2.0f - 100.0f;
  StartPlayer(&Window);
  ResetCleanable(&c);
  return 1;
}

void End() {
  FreeSprite(&Background);
  FreeSprite(&Background2);
  FreeSprite(&Background3);
  FreeSprite(&CleanedText);
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
    // printf("MAIN MENU\n");
    if (gameStart) {
      timerLastTime = (float)SDL_GetTicks() / 1000.0f;
      gameState = PREPARING;
    }
  }
  if (gameState == PREPARING) {
    timerCurrentTime = (float)SDL_GetTicks() / 1000.0f;
    if (timerCurrentTime - timerLastTime >= 5.0f) {
      InitGame();
      gameState = PLAYING;
    }
  }
  if (gameState == PLAYING) {
    // printf("PLAYING\n");

    if (plate.state == WASHING)
      player.atlasX = 1;
    else
      player.atlasX = 0;
    timerCurrentTime = (float)SDL_GetTicks() / 1000.0f;

    if (!timerFinished) {

      if (timerCurrentTime - timerLastTime >= 1.0f) {
        countdown.value -= 1;

        timerLastTime = timerCurrentTime;
        if (countdown.value <= 0)
          timerFinished = 1;
      }
      FollowMouse(mouse.posX, mouse.posY, dt);
      PlateUpdate(&plate, &c, &mouse, &cleanedPlates.value, dt);
    } else {
      if (timerCurrentTime - timerLastTime >= 5.0f) {
        gameState = RESULT_SCREEN;
        timerLastTime = timerCurrentTime;
      }
    }

  } else if (gameState == RESULT_SCREEN) {
    timerCurrentTime = (float)SDL_GetTicks() / 1000.0f;
    if (timerCurrentTime - timerLastTime >= 5.0f) {
      gameState = MAIN_MENU;
      timerLastTime = timerCurrentTime;
      gameStart = 0;
    }
  }
}

void Display() {
  ClearWindow(&Window);
  // Logica de renderizado

  if (gameState == MAIN_MENU) {
    DrawCoverSprite(&Window, &Background2);
  } else if (gameState == PREPARING) {
    DrawCoverSprite(&Window, &Background3);
  } else if (gameState == PLAYING) {
    DrawCoverSprite(&Window, &Background);
    DrawPlate(&Window, &plate, &c);
    DrawPlayer(&Window);
    DrawTextNumber(&Window, &countdown, 0.0f, 0.0f);
  } else if (gameState == RESULT_SCREEN) {
    DrawCoverSprite(&Window, &Background);
    DrawSprite(&Window, &CleanedText);
    DrawTextNumber(&Window, &cleanedPlates, CleanedText.posX + 600.0f,
                   CleanedText.posY + 50.0f);
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
      else if (e.key.key == SDLK_RETURN && gameState == MAIN_MENU)
        gameStart = 1;
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

void InitGame() {
  timerLastTime = (float)SDL_GetTicks() / 1000.0f;
  c.nCleanables = 5;
  ResetCleanable(&c);
  plate.sprite.posX = -600.0f;
  plate.state = ENTERING;
  countdown.value = 150;
  cleanedPlates.value = 0;
  timerFinished = 0;
  gameState = PLAYING;
}
