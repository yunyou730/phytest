#include "InspectorGuiSystem.h"

#include "fila.h"
#include "Entity.h"
#include <vector>

#include "TransformComponent.h"
#include "CameraComponent.h"

#include "WorldComp.h"

#include "imgui.h"
#include <sstream>

#include "Inspector/InspectorItemTransform.h"
#include "Inspector/InspectorItemCamera.h"
#include "Inspector/InspectorItemRenderState.h"

#include "ComponentFactory.h"

namespace ad {

static const char* componentTags[] = {
    "CameraComponent",
    "PrimitiveComponent",
    "RenderStateComponent",
    "Phy2DComponent",
};

InspectorGuiSystem::InspectorGuiSystem(fl::Framework* framework)
    :System(framework)
{
    _entitySelection = GetFramework()->GetWorldComponent<WCEntitySelection>();
}

void InspectorGuiSystem::OnGUI()
{
    // deal position
    ImGuiIO io = ImGui::GetIO();
    float display_width = (float) io.DisplaySize.x;
    float display_height = (float)io.DisplaySize.y;
    float demo_window_size_x = display_width * 0.25;
    float demo_window_size_y = display_height * 0.8;
    
    float demo_window_pos_x = display_width - demo_window_size_x;
    float demo_window_pos_y = display_height * 0;

    ImGui::SetNextWindowPos(ImVec2(demo_window_pos_x, demo_window_pos_y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(demo_window_size_x,demo_window_size_y),ImGuiCond_Once);
    
    
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
    
    ShowAddComponentPart(entity);
    if(ImGui::Button("Add Component"))
    {
        DoAddComponent(_toAddComponentIndex,entity);
    }
    
    InspectorItemTransform::Show(entity);
    InspectorItemCamera::Show(entity);
    InspectorItemRenderState::Show(entity);
}

void InspectorGuiSystem::ShowAddComponentPart(fl::Entity* entity)
{
    struct Funcs {
        static bool ItemGetter(void* data, int n, const char** out_str) {
            *out_str = ((const char**)data)[n];
            return true;
        }
    };
    ImGui::Combo("select component", &_toAddComponentIndex, &Funcs::ItemGetter, componentTags, IM_ARRAYSIZE(componentTags));
}


void InspectorGuiSystem::DoAddComponent(int index,fl::Entity* entity)
{
    ComponentFactory::CreateComponent(componentTags[index],entity);
}

}
