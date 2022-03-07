#include "InspectorGuiSystem.h"

#include "fila.h"
#include "Entity.h"
#include <vector>

#include "TransformComponent.h"
#include "CameraComponent.h"

#include "WorldComp.h"

#include "imgui.h"
#include <sstream>

namespace ad {

InspectorGuiSystem::InspectorGuiSystem(fl::Framework* framework)
    :System(framework)
{
    _entitySelection = GetFramework()->GetWorldComponent<WCEntitySelection>();
}

void InspectorGuiSystem::OnGUI()
{
    ImGuiWindowFlags window_flags = 0;
    bool* p_open = nullptr;
    
    if (ImGui::Begin("Inspector", p_open, window_flags))
    {
        fl::Entity* entity = GetFramework()->GetEntity(_entitySelection->selectedEntityID);
        if(entity != nullptr)
        {
            RefreshInspector(entity);
        }
    }
    ImGui::End();
}

void InspectorGuiSystem::RefreshInspector(fl::Entity* entity)
{
    ImGui::Text("[EntityID] %d",entity->GetID());
    
    if (ImGui::CollapsingHeader("TransformComponent"))
    {
        auto transform = entity->GetComponent<fl::TransformComponent>();
        
        ImGui::Text("Position");
        ImGui::InputFloat("x", &transform->_pos.x);
        ImGui::InputFloat("y", &transform->_pos.y);
        ImGui::InputFloat("z", &transform->_pos.z);
    }
}

}
