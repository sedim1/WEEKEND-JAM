#include "Number.h"
#include "Global.h"
#include "RenderWindow.h"
#include "Sprite.h"
TEXT_NUMBER textNumber(RenderWindow *Window) {
  TEXT_NUMBER n = {0, NewSprite(Window, "Assets/Textures/Numbers.png", 16, 31)};
  return n;
}
void DrawTextNumber(RenderWindow *Window, TEXT_NUMBER *t, float posX,
                    float posY) {
  int nDigits = CountDigits(t->value);
  for (int i = 0; i < nDigits; i++) {
    t->texture.posX = posX + (i * t->texture.width * SPRITE_SCALE);
    t->texture.posY = posY;
    int currentDigit = GetDigit(t->value, nDigits - i);
    t->texture.atlasX = currentDigit;
    DrawSprite(Window, &t->texture);
  }
}
