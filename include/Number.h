#ifndef NUMBER_H
#define NUMBER_H

#include "RenderWindow.h"
#include "Sprite.h"
typedef struct {
  int value;
  Sprite texture;
} TEXT_NUMBER;

TEXT_NUMBER textNumber(RenderWindow *Window);
void DrawTextNumber(RenderWindow *Window, TEXT_NUMBER *t, float posX,
                    float posY);

#endif
