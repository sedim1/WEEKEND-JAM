#ifndef PLAYER_H
#define PLAYER_H

#include "RenderWindow.h"
#include "Sprite.h"

typedef Sprite Player;

void StartPlayer(RenderWindow *Window);
void FollowMouse(float posX, float posY, float dt);
void EndPlayer();
void DrawPlayer(RenderWindow *Window);

#endif // !PLAYER_H
