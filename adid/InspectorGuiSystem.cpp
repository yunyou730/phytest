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
    
    if (ImGui::CollapsingHeader(fl::TransformComponent::ClsName(),true))
    {
        auto transform = entity->GetComponent<fl::TransformComponent>();
        
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
    
    
    const static char* cameraTypeItems[] = {"Perspective","Ortho"};
    auto camera = entity->GetComponent<fl::CameraComponent>();
    if(camera != nullptr && ImGui::CollapsingHeader(fl::CameraComponent::ClsName(),true))
    {
        int selectIndex = (int)camera->_cameraType;
        ImGui::Combo("camera_type", &selectIndex, cameraTypeItems, IM_ARRAYSIZE(cameraTypeItems));
        camera->_cameraType = (fl::ECameraType)selectIndex;
        
        ImGui::DragInt("camera_sort",&camera->_sort,1,0,20);
        ImGui::DragFloat("camera_fov_y", &camera->_fovY,1.f,0.f,180.f);
        
        ImGui::DragFloat("camera_move_speed",&camera->_moveSpeed,1.f,0.f,30.f);
        ImGui::DragFloat("camera_rot_speed",&camera->_rotateDegSpeed,1.f,0.f,360.f);
        
        // look dir
        std::stringstream ss;
        ImGui::Text("look dir(%.3f,%.3f,%.3f)",camera->LookDir().x,camera->LookDir().y,camera->LookDir().z);
        
        // render layers
        ss.clear();
        for(auto it = camera->_renderLayers.begin();it != camera->_renderLayers.end();it++)
        {
            ss << *it << ",";
        }
        ImGui::Text("render layers [%s]",ss.str().c_str());
    }
}

}
