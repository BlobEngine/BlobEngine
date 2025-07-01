#pragma once
#include "../../external/Imgui-SFML/include/imgui-SFML.h"
#include "../../external/Imgui/include/imgui.h"
#include "../../include/core/gameobjects/shape.h"
#include "../../include/core/gameobjects/spring.h"

#include "../../include/core/physics/verlet.h"
#include "../../include/core/physics/collision.h"
#include "../../include/core/physics/springforce.h"

#include <cstddef>
#include <vector>

namespace Editor {

	namespace DebugMenu {

		inline float restLength = 100.0f;
		inline float springConstant = 60.0f;
		inline float pointMass = Point::mass;
		inline float pointRadius = Point::radius;
		inline float pointRestitution = Point::restitution;
		inline int newMaxPoints = 10;
		inline bool activeCircleCollide = false;

		void Init();
		void WorldSetup();
		void PointSetup(SpringSystem& springs);
		void SpringSetup(SpringSystem& springs);
		void Apply(SpringSystem& springs);
		void Draw(SpringSystem& springs);

	}

}
