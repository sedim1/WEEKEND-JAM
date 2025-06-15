#ifndef PLATES_H
#define PLATES_H

#include "Cleanable.h"
#include "Mouse.h"
#include "RenderWindow.h"
#include "Sprite.h"

enum PlateState {
  ENTERING,
  DIRTY,
  WASHING,
  DRYING,
  CLEANED_UP,
  BROKEN,
  EXITING,
};

typedef struct {
  enum PlateState state;
  Sprite sprite;
  float durability;
  float sensibility;
} Plate;

Plate NewPlate(RenderWindow *Window);
void PlateUpdate(Plate *plate, Cleanables *c, Mouse *mouse, float dt);
void DrawPlate(RenderWindow *Window, Plate *plate, Cleanables *c);

#endif // !PLATES_H
