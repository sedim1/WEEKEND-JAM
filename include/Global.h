#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 320 * 4
#define SCREEN_HEIGHT 224 * 4
#define SPRITE_SCALE 4.0f

float Lerp(float from, float to, float t);
float Length(float x, float y);

int RandomNumberInRange(int min, int max);

int farEnough(float x1, float y1, float x2, float y2, float minDist);

#endif
