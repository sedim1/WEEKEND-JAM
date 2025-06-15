#include "Cleanable.h"
#include "CircleCollider.h"
#include "Global.h"
#include "RenderWindow.h"
#include "Sprite.h"

Cleanables clenables(RenderWindow *Window) {
  Cleanables cleanables;
  cleanables.nCleanables = 8;
  for (int i = 0; i < MAX; i++) {
    cleanables.dirt[i] =
        NewSprite(Window, "Assets/Textures/Cleanables.png", 32, 28);
    cleanables.dirt[i].atlasX = 0;
    cleanables.d[i] = IS_ON;
    cleanables.spume[i] =
        NewSprite(Window, "Assets/Textures/Cleanables.png", 32, 28);
    cleanables.spume[i].atlasX = 1;
    cleanables.spume[i].size = 0.0f;
    cleanables.s[i] = IS_OFF;
  }
  return cleanables;
}

void TranslateRelativeToPlate(float posX, float posY, Cleanables *cleanables) {
  for (int i = 0; i < cleanables->nCleanables; i++) {
    cleanables->dirt[i].posX = posX + cleanables->xRelDirt[i];
    cleanables->dirt[i].posY = posY + cleanables->yRelDirt[i];
    cleanables->spume[i].posX = posX + cleanables->xRelSpume[i];
    cleanables->spume[i].posY = posY + cleanables->yRelSpume[i];
  }
}

void EndCleanables(Cleanables *c) {
  for (int i = 0; i < MAX; i++) {
    FreeSprite(&c->dirt[i]);
    FreeSprite(&c->spume[i]);
  }
}

void DrawCleanables(RenderWindow *Window, Cleanables *c) {
  for (int i = 0; i < c->nCleanables; i++) {
    DrawSprite(Window, &c->dirt[i]);
    DrawSprite(Window, &c->spume[i]);
  }
}

void AssignRandomPositions(Cleanables *c) {
  float lastXD = 0.0f;
  float lastYD = 0.0f;
  float lastXS = 0.0f;
  float lastYS = 0.0f;
  for (int i = 0; i < c->nCleanables; i++) {
    do {
      c->xRelDirt[i] = RandomNumberInRange(80, 480);
      c->yRelDirt[i] = RandomNumberInRange(80, 480);
    } while (!farEnough(c->xRelDirt[i], c->yRelDirt[i], lastXD, lastYD,
                        43.0 * SPRITE_SCALE));
    lastXD = c->xRelDirt[i];
    lastYD = c->yRelDirt[i];
    do {
      c->xRelSpume[i] = RandomNumberInRange(80, 480);
      c->yRelSpume[i] = RandomNumberInRange(80, 480);
    } while (!farEnough(c->xRelSpume[i], c->yRelSpume[i], lastXS, lastYS,
                        43.0 * SPRITE_SCALE));

    lastXS = c->xRelSpume[i];
    lastYS = c->yRelSpume[i];
  }
}

void ResetCleanable(Cleanables *c) {
  for (int i = 0; i < c->nCleanables; i++) {
    c->dirt[i].size = 1;
    c->d[i] = IS_ON;
    c->spume[i].size = 0;
    c->s[i] = IS_OFF;
  }
  AssignRandomPositions(c);
}

int isWashed(Cleanables *c) {
  int flag = 0;
  for (int i = 0; i < c->nCleanables; i++) {
    if (c->d[i] == IS_OFF && c->s[i] == IS_ON) {
      flag = 1;
    } else {
      flag = 0;
      break;
    }
  }
  return flag;
}

int isCleaned(Cleanables *c) {
  int flag = 1;
  for (int i = 0; i < c->nCleanables; i++) {
    if (c->s[i] == IS_OFF) {
      flag = 1;
    } else {
      flag = 0;
      break;
    }
  }
  return flag;
}

void getWashed(CircleCollider *mouseCollider, float speed, Cleanables *c,
               float dt) {
  for (int i = 0; i < c->nCleanables; i++) {
    CircleCollider circle = {
        c->dirt[i].posX + 64.0f * c->dirt[i].size,
        c->dirt[i].posY + 56.0f * c->dirt[i].size,
        64,
    };

    CircleCollider circle2 = {
        (c->spume[i].posX + 64.0f * c->spume[i].size),
        (c->spume[i].posY + 56.0f * c->spume[i].size),
        64,
    };

    // printf("%d\n", CircleToCircleCollision(mouseCollider, &circle));
    if (CircleToCircleCollision(mouseCollider, &circle) && speed >= 2.0f) {
      c->dirt[i].size -= 1.5f * dt;
      if (c->dirt[i].size <= 0.2f) {
        c->dirt[i].size = 0.0f;
        c->d[i] = IS_OFF;
      }
    }
    if (CircleToCircleCollision(mouseCollider, &circle2) && speed >= 2.0f) {
      c->spume[i].size += 1.5f * dt;
      if (c->spume[i].size >= 0.8f) {
        c->spume[i].size = 1.0f;
        c->s[i] = IS_ON;
      }
    }
  }
}

void getCleaned(CircleCollider *mouseCollider, float speed, Cleanables *c,
                float dt) {
  for (int i = 0; i < c->nCleanables; i++) {

    CircleCollider circle = {
        (c->spume[i].posX + 64.0f * c->spume[i].size),
        (c->spume[i].posY + 56.0f * c->spume[i].size),
        64,
    };
    if (CircleToCircleCollision(mouseCollider, &circle) && speed >= 2.0f) {
      c->spume[i].size -= 1.5f * dt;
      if (c->spume[i].size <= 0.2f) {
        c->spume[i].size = 0.0f;
        c->s[i] = IS_OFF;
      }
    }
  }
}
