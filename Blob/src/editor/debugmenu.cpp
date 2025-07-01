#include "../../include/editor/debugmenu.h"

namespace Editor {
    float restLength = 100.0f;
    float springConstant = 60.0f;
    float pointMass = Point::mass;
    float pointRadius = Point::radius;
    float pointRestitution = Point::restitution;

    void DrawDebugMenu(std::vector<Spring>& springs) {

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(250, 0), ImGuiCond_Always); // fixed width, full height

        ImGui::Begin("DebugMenu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::PushItemWidth(60);

        // World Properties (Gravity + Damping)
        if (ImGui::CollapsingHeader("World Properties")) {
            ImGui::Text("Gravity");

            // Horizontal layout for X and Y
            {
                // --- Dark Red "X" Button ---
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(128, 32, 32, 255)); // Dark red
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(160, 50, 50, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(128, 32, 32, 255));
                ImGui::Button("X");
                ImGui::PopStyleColor(3);
                ImGui::SameLine();

                ImGui::InputFloat("##gravityX", &PhysicsEngine::Verlet::gravity.x);
            }

            {
                // --- Dark Green "Y" Button ---
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(32, 128, 32, 255)); // Dark green
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(50, 160, 50, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(32, 128, 32, 255));
                ImGui::Button("Y");
                ImGui::PopStyleColor(3);
                ImGui::SameLine();

                ImGui::InputFloat("##gravityY", &PhysicsEngine::Verlet::gravity.y);
            }

            ImGui::InputFloat("Damping##damping", &PhysicsEngine::Verlet::damping);
        }

        // Point Properties
        if (ImGui::CollapsingHeader("Point Properties")) {
            ImGui::InputFloat("Mass##mass", &pointMass, 0.0f, 0.0f, "%.2f");
            ImGui::InputFloat("Radius##radius", &pointRadius, 0.0f, 0.0f, "%.2f");
            ImGui::InputFloat("Restitution##restitution", &pointRestitution, 0.0f, 0.0f, "%.2f");
        }

        // Spring Properties
        if (ImGui::CollapsingHeader("Spring Properties")) {
            ImGui::InputFloat("Rest Length", &restLength, 0.0f, 0.0f, "%.2f");
            ImGui::InputFloat("Spring Constant", &springConstant, 0.0f, 0.0f, "%.2f");
        }

        // Apply changes to all springs & points
        for (auto& spring : springs) {
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
