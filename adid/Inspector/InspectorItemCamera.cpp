#include "imgui.h"

#include "InspectorItemCamera.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

const static char* cameraTypeItems[] = {"Perspective","Ortho"};

namespace ad
{

void InspectorItemCamera::Show(fl::Entity* entity)
{
    auto camera = entity->GetComponent<fl::CameraComponent>();
    if(camera == nullptr) return;
 

    if(camera != nullptr && ImGui::CollapsingHeader(fl::CameraComponent::ClsName(),ImGuiTreeNodeFlags_DefaultOpen))
    {
        int selectIndex = (int)camera->_cameraType;
        ImGui::Combo("camera_type", &selectIndex, cameraTypeItems, IM_ARRAYSIZE(cameraTypeItems));
        camera->_cameraType = (fl::ECameraType)selectIndex;
        
        ImGui::DragInt("camera_sort",&camera->_sort,1,0,20);
        ImGui::DragFloat("camera_fov_y", &camera->_fovY,1.f,0.f,180.f);
        
        ImGui::DragFloat("camera_move_speed",&camera->_moveSpeed,1.f,0.f,30.f);
        ImGui::DragFloat("camera_rot_speed",&camera->_rotateDegSpeed,1.f,0.f,360.f);
        
        
        ImGui::DragFloat("camera_ortho_half",&camera->_orthoHalf,0.5f,0.3f,30.f);

        
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


