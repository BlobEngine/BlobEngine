#include "../../include/editor/debugmenu.h"

namespace Editor {

    float pointMass = Point::mass;
    float pointRadius = Point::radius;
    float pointRestitution = Point::restitution;

    void DrawDebugMenu(Shape& shape) {
        ImGui::PushItemWidth(60);

        // Gravity Controls
        ImGui::Text("Gravity");
        ImGui::InputFloat("X", &PhysicsEngine::Verlet::gravity.x);
        ImGui::SameLine();
        ImGui::InputFloat("Y", &PhysicsEngine::Verlet::gravity.y);

        // Damping
        ImGui::InputFloat("Damping", &PhysicsEngine::Verlet::damping);

        // Point Controls
        ImGui::Separator();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Point Properties");

        ImGui::InputFloat("Mass", &pointMass, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Radius", &pointRadius, 0.0f, 0.0f, "%.2f");
        ImGui::InputFloat("Restitution", &Point::restitution, 0.0f, 0.0f, "%.2f");

        // Apply changes to all points
        for (auto& point : shape.points) {
            point.mass = pointMass;
            point.radius = pointRadius;
            point.restitution = pointRestitution;
        }

        ImGui::PopItemWidth();
    }

} // namespace Editor
