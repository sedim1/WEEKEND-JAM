#include "Plates.h"
#include "CircleCollider.h"
#include "Cleanable.h"
#include "Global.h"
#include "Sprite.h"
#include <stdio.h>

// Position at center
// plate.sprite.posY = SCREEN_HEIGHT / 8.0f;
//  plate.sprite.posX = SCREEN_WIDTH / 4.0f;

// Top left positions
float centerPos[2] = {
    SCREEN_WIDTH / 4.0f,
    SCREEN_HEIGHT / 8.0f,
};

float outX = -900.0f;

int t = 0.0f;

Plate NewPlate(RenderWindow *Window) {
  Plate plate = {ENTERING,
                 NewSprite(Window, "Assets/Textures/Plates.png", 82, 82),
                 100.0f, 1.0f};
  plate.sprite.size = 2.0f;
  plate.sprite.posY = centerPos[1];
  plate.sprite.posX = -600.0f;
  plate.sprite.atlasX = 1;
  //  plate.sprite.posX = -500.0f;
  return plate;
}

void PlateUpdate(Plate *plate, Cleanables *c, Mouse *mouse, int *counter,
                 float dt) {
  TranslateRelativeToPlate(plate->sprite.posX, plate->sprite.posY, c);

  if (plate->state == ENTERING) {
    // printf("ENTERING\n");
    plate->sprite.posX += 2300.0f * dt;
    if (plate->sprite.posX >= centerPos[0]) {
      plate->state = DIRTY;
      plate->sprite.posX = centerPos[0];
      plate->sprite.atlasX = 1;
    }
  } else if (plate->state == EXITING) {
    // printf("EXITING\n");
    plate->sprite.posX += 2300.0f * dt;
    if (plate->sprite.posX >= SCREEN_WIDTH + 10) {
      plate->sprite.atlasX = 1;
      plate->state = ENTERING;
      plate->sprite.posX = -600.0f;
      ResetCleanable(c);
      t = 0.0f;
    }
  } else if (plate->state != BROKEN) {
    plate->sprite.atlasX = 1;
    // Data for plate collision
    float mouseSpeed = Length(mouse->relX, mouse->relY);
    CircleCollider plateCollider = {plate->sprite.posX + SCREEN_WIDTH / 4.0f,
                                    plate->sprite.posY + SCREEN_WIDTH / 4.0f,
                                    82 * SPRITE_SCALE};
    CircleCollider mouseCollider =
        circleCollider(mouse->posX, mouse->posY, 64.0f);

    // Run plate logic
    if (mouseSpeed >= 2.0 && mouse->isPressed &&
        CircleToCircleCollision(&mouseCollider, &plateCollider)) {
      if (plate->state == DIRTY) {
        // printf("DIRTY\n");
        //  plate->durability -= mouseSpeed * plate->sensibility * dt;
        getWashed(&mouseCollider, mouseSpeed, c, dt);
        if (isWashed(c))
          plate->state = WASHING;
      } else if (plate->state == WASHING) {
        // printf("WASHING\n");
        getCleaned(&mouseCollider, mouseSpeed, c, dt);
        if (isCleaned(c)) {
          plate->state = CLEANED_UP;
        }
      } else if (plate->state == CLEANED_UP) {
        // printf("PLATE CLEANED\n");
        *counter += 1;
        c->nCleanables += 1;
        if (c->nCleanables >= MAX) {
          c->nCleanables = MAX - 1;
        }
        plate->state = EXITING;
        plate->sprite.atlasX = 0;
      }
    }
  }
}

void DrawPlate(RenderWindow *Window, Plate *plate, Cleanables *c) {
  DrawSprite(Window, &plate->sprite);
  if (plate->state != EXITING)
    DrawCleanables(Window, c);
}
