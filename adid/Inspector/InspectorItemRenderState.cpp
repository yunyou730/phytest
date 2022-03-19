#include "imgui.h"

#include "InspectorItemRenderState.h"
#include "Entity.h"
#include "RenderStateComponent.h"

const static char* primitiveTypeItem[] = {"Triangle","Point","Line"};

namespace ad
{

void InspectorItemRenderState::Show(fl::Entity* entity)
{
    auto comp = entity->GetComponent<fl::RenderStateComponent>();
     if (comp != nullptr && ImGui::CollapsingHeader(fl::RenderStateComponent::ClsName(),ImGuiTreeNodeFlags_DefaultOpen))
     {
         int selectIndex = (int)comp->_primitiveType;
         ImGui::Combo("render_primitive_type", &selectIndex, primitiveTypeItem, IM_ARRAYSIZE(primitiveTypeItem));
         comp->_primitiveType = (fl::ERenderPrimitiveType)selectIndex;
         
         ImGui::DragFloat("render_point_size",&comp->_pointSize,0.0f,0.0f,100.0f);
         ImGui::Checkbox("render_enable_zTest",&comp->_bEnableDepthTest);
         ImGui::DragInt("render_layerIndex",&comp->_renderLayerInex);
     }

}

}


