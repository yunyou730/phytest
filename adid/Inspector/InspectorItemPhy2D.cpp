#include "imgui.h"

#include "InspectorItemPhy2D.h"
#include "Entity.h"
#include "PrimitiveComponent.h"



namespace ad
{

void InspectorItemPhy2D::Show(fl::Entity* entity)
{
    auto comp = entity->GetComponent<fl::PrimitiveComponent>();
     if (comp != nullptr && ImGui::CollapsingHeader(fl::PrimitiveComponent::ClsName(),ImGuiTreeNodeFlags_DefaultOpen))
     {
         
     }

}

}


