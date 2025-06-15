#include "CircleCollider.h"
#include "Global.h"

CircleCollider circleCollider(float x, float y, float radius) {
  return (CircleCollider){x, y, radius};
}

int CircleToCircleCollision(const CircleCollider *A, const CircleCollider *B) {
  int isColliding = 0;
  float dx = A->x - B->x;
  float dy = A->y - B->y;
  float distance = Length(dx, dy);

  if (distance <= A->radius + B->radius)
    isColliding = 1;

  return isColliding;
}
