#include "../../include/editor/debugmenu.h"

namespace Editor {
float restLength = 100.0f;
float springConstant = 60.0f;
float pointMass = Point::mass;
float pointRadius = Point::radius;
float pointRestitution = Point::restitution;

void DrawDebugMenu(std::vector<Spring> &springs) {
  ImGui::PushItemWidth(60);

  // Gravity Controls
  ImGui::Text("Gravity");
  ImGui::InputFloat("X", &PhysicsEngine::Verlet::gravity.x);
  ImGui::SameLine();
  ImGui::InputFloat("Y", &PhysicsEngine::Verlet::gravity.y);

  // Damping
  ImGui::InputFloat("Damping", &PhysicsEngine::Verlet::damping);

  // Spring Controls
  ImGui::Separator();
  ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Spring Properties");
  ImGui::InputFloat("RestLength", &restLength, 0.0f, 0.0f, "%.2f");
  ImGui::InputFloat("SpringConstant", &springConstant, 0.0f, 0.0f, "%.2f");

  // Point Controls
  ImGui::Separator();
  ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Point Properties");

  ImGui::InputFloat("Mass", &pointMass, 0.0f, 0.0f, "%.2f");
  ImGui::InputFloat("Radius", &pointRadius, 0.0f, 0.0f, "%.2f");
  ImGui::InputFloat("Restitution", &pointRestitution, 0.0f, 0.0f, "%.2f");

  // Apply changes to all points
  for (auto &spring : springs) {
    spring.restLength = restLength;
    spring.springConstant = springConstant;
    spring.a->mass = pointMass;
    spring.b->mass = pointMass;
    spring.a->radius = pointRadius;
    spring.b->radius = pointRadius;
    spring.a->restitution = pointRestitution;
    spring.b->restitution = pointRestitution;
  }

  ImGui::PopItemWidth();
}

} // namespace Editor
