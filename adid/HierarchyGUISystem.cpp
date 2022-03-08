#include "HierarchyGUISystem.h"

#include "fila.h"
#include "Entity.h"
#include <vector>

#include "TransformComponent.h"
#include "CameraComponent.h"

#include "WorldComp.h"

#include "imgui.h"
#include <sstream>

namespace ad {

HierarychyGUISystem::HierarychyGUISystem(fl::Framework* framework)
    :System(framework)
{
    _entitySelection = GetFramework()->GetWorldComponent<WCEntitySelection>();
}

void HierarychyGUISystem::OnGUI()
{
    ImGuiWindowFlags window_flags = 0;
    bool* p_open = nullptr;
    
    if (ImGui::Begin("Hierarchy", p_open, window_flags))
    {
        ImGui::SetNextItemOpen(_hierarchyExpand);
        
        const std::map<unsigned int,fl::Entity*>& entityMap = GetFramework()->GetEntityMap();
        if (ImGui::TreeNode("Root"))
        {
            for(auto it = entityMap.begin();it != entityMap.end();it++)
            {
                fl::Entity* entity = it->second;
                
                std::stringstream ss;
                ss << "[Entity ID] " << entity->GetID();
                
                if(ImGui::Selectable(ss.str().c_str(),entity->GetID() == _entitySelection->selectedEntityID))
                {
                    _entitySelection->selectedEntityID = entity->GetID();
                }
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();
}


}
