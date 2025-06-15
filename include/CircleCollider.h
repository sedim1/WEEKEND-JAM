#ifndef CIRCLE_COLLIDER
#define CIRCLE_COLLIDER

typedef struct {
  float x, y;
  float radius;
} CircleCollider;

CircleCollider circleCollider(float x, float y, float radius);
int CircleToCircleCollision(const CircleCollider *A, const CircleCollider *B);

#endif
