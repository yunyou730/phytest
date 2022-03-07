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
    
}

void HierarychyGUISystem::OnGUI()
{
    
    ImGuiWindowFlags window_flags = 0;
    bool* p_open = nullptr;
    
    if (ImGui::Begin("Hierarchy", p_open, window_flags))
    {
        const std::map<unsigned int,fl::Entity*>& entityMap = GetFramework()->GetEntityMap();
        if (ImGui::TreeNode("Root"))
        {
            for(auto it = entityMap.begin();it != entityMap.end();it++)
            {
                fl::Entity* entity = it->second;
                
                std::stringstream ss;
                ss << entity->GetID();
                
                if(ImGui::Button(ss.str().c_str()))
                {
                    auto entitySel = GetFramework()->GetWorldComponent<WCEntitySelection>();
                    entitySel->selectedEntityID = entity->GetID();
                }
            }
            ImGui::TreePop();
        }


    }
    ImGui::End();
    
    

}


}
