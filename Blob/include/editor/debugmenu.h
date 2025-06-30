#pragma once
#include "../../external/Imgui-SFML/include/imgui-SFML.h"
#include "../../external/Imgui/include/imgui.h"
#include "../../include/core/gameobjects/shape.h"
#include "../../include/core/physics/physics.h"
#include "core/gameobjects/spring.h"
#include <cstddef>
#include <vector>

namespace Editor {
void DrawDebugMenu(std::vector<Spring> &springs);
}
