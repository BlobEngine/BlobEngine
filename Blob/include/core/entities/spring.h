#pragma once
#include "../../core/entities/point.h"
#include "../../core/entities/shape.h"

struct Spring {

  Point *a;
  Point *b;

  float restLength = 100.f;
  float springConstant = 60.0f;
};

struct SpringSystem {

  std::vector<Spring> springs;

  void InitAll(Shape &shape, Spring &spring);
  void UpdateAll(Shape &shape, Spring &spring);
  void Setup(float dt);
  void Draw(sf::RenderWindow &window);

  // EXTRAS
  void InitPerMesh(Shape &shape, Spring &spring);
  void InitPerVertex(Shape &shape, Spring &spring);
  void InitRadialCenter(Shape &shape, Spring &spring);
  void InitCircular(Shape &shape, Spring &spring);
  void InitCircularCenter(Shape &shape, Spring &spring);
};
