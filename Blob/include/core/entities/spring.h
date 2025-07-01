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

	void InitDefault(Shape& shape, Spring& spring);
	void Setup(float dt);
	void Draw(sf::RenderWindow& window);

	// Rope Simulation
	void InitRope(Shape& shape, Spring& spring);
};