#include "../../include/editor/debugmenu.h"

namespace Editor {
int pointMass = 5;
float pointRadius = 10.0f;
float pointRestitution = 0.85f;

void drawDebugMenu(Shape &shape) {
  ImGui::PushItemWidth(60);
  ImGui::InputFloat("Gravity X", &PhysicsEngine::Verlet::gravityX);
  ImGui::SameLine();
  ImGui::InputFloat("Gravity Y", &PhysicsEngine::Verlet::gravityY);
  ImGui::InputFloat("Damping", &PhysicsEngine::Verlet::damping);
  ImGui::TextColored(ImVec4{255, 0, 0, 255}, "Point Properties:");
  ImGui::InputInt("Mass", &pointMass, 0, 0);
  ImGui::InputFloat("Radius", &pointRadius);
  ImGui::InputFloat("Restitution", &pointRestitution);
  for (auto &point : shape.points) {
    point.mass = pointMass;
    point.radius = pointRadius;
    point.restitution = pointRestitution;
  }
  ImGui::PopItemWidth();
}
} // namespace Editor
