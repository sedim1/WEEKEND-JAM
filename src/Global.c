#include "Global.h"
#include <math.h>
#include <stdlib.h>

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

int CountDigits(int a) {
  // For digit 0
  if (a == 0)
    return 1;

  int count = 0;

  // Remove last digit from number
  // till number is 0
  while (a != 0) {

    // Increment count
    count++;
    a /= 10;
  }

  // return the count of digit
  return count;
}

// 0 - least significant, last Index, most significant
int GetDigit(int n, int index) {
  int digit = 0;
  int i = 0;
  if (n == 0)
    return 0;
  do {
    digit = n % 10;
    n /= 10;
    i++;
  } while (i < index);
  return digit;
}
