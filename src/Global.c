#include "Global.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

float Lerp(float from, float to, float t) { return (from + t * (to - from)); }

float Length(float x, float y) { return sqrtf(x * x + y * y); }

int RandomNumberInRange(int min, int max) {
  int randomNumber = (rand() % (max - min + 1)) + min;
  return randomNumber;
}

int farEnough(float x1, float y1, float x2, float y2, float minDist) {
  int flag = 0;
  float dx = x2 - x1;
  float dy = y2 - y1;
  if (Length(dx, dy) >= minDist)
    flag = 1;
  return flag;
}
