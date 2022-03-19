#include "imgui.h"

#include "InspectorItemPrimitive.h"
#include "Entity.h"
#include "PrimitiveComponent.h"



namespace ad
{

void InspectorItemPrimitive::Show(fl::Entity* entity)
{
    auto comp = entity->GetComponent<fl::PrimitiveComponent>();
     if (comp != nullptr && ImGui::CollapsingHeader(fl::PrimitiveComponent::ClsName(),ImGuiTreeNodeFlags_DefaultOpen))
     {
         
     }

}

}


