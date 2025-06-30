#pragma once
#include "../../core/gameobjects/point.h"

struct Spring {
  Point *a;
  Point *b;
  float restLength;
  float springConstant;

  Spring(Point *a_, Point *b_, float r, float k)
      : a(a_), b(b_), restLength(r), springConstant(k) {}
};
