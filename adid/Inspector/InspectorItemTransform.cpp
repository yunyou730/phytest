#include "imgui.h"

#include "InspectorItemTransform.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace ad
{

void InspectorItemTransform::Show(fl::Entity* entity)
{
    auto transform = entity->GetComponent<fl::TransformComponent>();
     if (transform != nullptr && ImGui::CollapsingHeader(fl::TransformComponent::ClsName(),ImGuiTreeNodeFlags_DefaultOpen))
     {
         ImGui::Text("Position");
         ImGui::DragFloat("px", &transform->_pos.x, 0.01f, 0.0f, 0.0f);
         ImGui::DragFloat("py", &transform->_pos.y, 0.01f, 0.0f, 0.0f);
         ImGui::DragFloat("pz", &transform->_pos.z, 0.01f, 0.0f, 0.0f);
         
         ImGui::Text("Rotation");
         ImGui::DragFloat("rx", &transform->_rotByEachAxis.x, 0.1f, 0.f, 360.f);
         ImGui::DragFloat("ry", &transform->_rotByEachAxis.y, 0.1f, 0.f, 360.f);
         ImGui::DragFloat("rz", &transform->_rotByEachAxis.z, 0.1f, 0.f, 360.f);
         
         ImGui::Text("Scale");
         ImGui::DragFloat("sx", &transform->_scale.x, 0.1f, 0.f, 0.f);
         ImGui::DragFloat("sy", &transform->_scale.y, 0.1f, 0.f, 0.f);
         ImGui::DragFloat("sz", &transform->_scale.z, 0.1f, 0.f, 0.f);
     }
}

}


