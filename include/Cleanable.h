#ifndef CLEANABLE_H
#define CLEANABLE_H

#include "CircleCollider.h"
#include "Global.h"
#include "RenderWindow.h"
#include "Sprite.h"

#define MAX 50

enum CleanableState {
  IS_ON,
  IS_OFF,
};

typedef struct {
  Sprite dirt[MAX], spume[MAX]; // positions will be relative to the plate
  int nCleanables;
  float xRelDirt[MAX], yRelDirt[MAX];
  float xRelSpume[MAX], yRelSpume[MAX];
  enum CleanableState d[MAX];
  enum CleanableState s[MAX];
} Cleanables;

Cleanables clenables(RenderWindow *Window);
void DrawCleanables(RenderWindow *Window, Cleanables *c);
void TranslateRelativeToPlate(float posX, float posY, Cleanables *cleanables);
void EndCleanables(Cleanables *c);
void AssignRandomPositions(Cleanables *c);

void ResetCleanable(Cleanables *c);

int isWashed(Cleanables *c);
int isCleaned(Cleanables *c);

// GameplayFunctions
void getWashed(CircleCollider *mouseCollider, float speed, Cleanables *c,
               float dt);

void getCleaned(CircleCollider *mouseCollider, float speed, Cleanables *c,
                float dt);

#endif // !dd
