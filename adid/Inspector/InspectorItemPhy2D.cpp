#include "imgui.h"

#include "InspectorItemPhy2D.h"
#include "Entity.h"
#include "Phy2DComponent.h"

namespace ad
{

void InspectorItemPhy2D::Show(fl::Entity* entity)
{
    auto comp = entity->GetComponent<fl::Phy2DComponent>();
     if (comp != nullptr && ImGui::CollapsingHeader(fl::Phy2DComponent::ClsName(),ImGuiTreeNodeFlags_DefaultOpen))
     {
         
     }
}

}


