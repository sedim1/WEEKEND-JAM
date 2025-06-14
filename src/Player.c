#include "Player.h"
#include "RenderWindow.h"
#include "Sprite.h"

Player player;
float followSpeed = 40.0f;

void StartPlayer(RenderWindow *Window) {
  player = NewSprite(Window, "Assets/Textures/Hand.png", 33, 58);
  player.atlasX = 1;
}

void FollowMouse(float posX, float posY, float dt) {
  player.posX = posX - 50.0f;
  player.posY = posY - 100.0f;
}

void DrawPlayer(RenderWindow *Window) { DrawSprite(Window, &player); }

void EndPlayer() { FreeSprite(&player); }
