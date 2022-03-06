#include "CameraCtrlSystem.h"

#include "fila.h"
#include "Entity.h"
#include <vector>

#include "TransformComponent.h"
#include "CameraComponent.h"

namespace ad {

CameraCtrlSystem::CameraCtrlSystem(fl::Framework* framework)
    :System(framework)
{
    _keyboardInput = _framework->GetWorldComponent<fl::WCKeyboardInput>(CLASS_NAME(WCKeyboardInput));
}

void CameraCtrlSystem::Update()
{
    DumpKeyboardState();
 
    float dt = _framework->GetApp()->GetDeltaTime();
    
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(CameraComponent));
    compSet.insert(CLASS_NAME(TransformComponent));
    std::vector<fl::Entity*> entities = GetFramework()->QueryEntityWithCompSet(compSet);
    
    for(auto it = entities.begin();it != entities.end();it++)
    {
        HandleCameraMove(dt,*it);
        HandleCameraRotate(dt,*it);
    }
}

void CameraCtrlSystem::DumpKeyboardState()
{
    printf("------------\n");
    for(int i = 0;i < (int)fl::EInputKey::Max;i++)
    {
        fl::EInputKey key = fl::EInputKey(i);
        fl::EKeyState state = _keyboardInput->GetState(key);
        
        printf("%d\t%d\n",key,state);
    }
    printf("------------\n");
}

void CameraCtrlSystem::HandleCameraMove(float deltaTime,fl::Entity* camEntity)
{
    auto transform = camEntity->GetComponent<fl::TransformComponent>(CLASS_NAME(TransformComponent));
    
    auto camComp = camEntity->GetComponent<fl::CameraComponent>(CLASS_NAME(CameraComponent));
    
    
    float distance = camComp->MoveSpeed() * _framework->GetApp()->GetDeltaTime();
    glm::vec3 direction(0.0);
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_UP))
    {
        direction = camComp->LookDir();
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_DOWN))
    {
        direction = -camComp->LookDir();
    }
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_LEFT))
    {
        direction = camComp->RightDir();
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_RIGHT))
    {
        direction = -camComp->RightDir();
    }
    
    if(glm::length(direction) > 0)
    {
        direction = glm::normalize(direction);
        transform->SetPosition(transform->GetPos() + direction * distance);
    }
}

void CameraCtrlSystem::HandleCameraRotate(float deltaTime,fl::Entity* camEntity)
{
    auto transform = camEntity->GetComponent<fl::TransformComponent>(CLASS_NAME(TransformComponent));
    
    auto camComp = camEntity->GetComponent<fl::CameraComponent>(CLASS_NAME(CameraComponent));
    
    float rotDegSpeed = camComp->RotSpeed();
    float rotDeg = rotDegSpeed * deltaTime;
    
    
    // @miao @todo
    
    glm::mat4 rot(1.0);
    glm::vec3 rotByEachAxis(0.0);
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_W))
    {
        rotByEachAxis.x += rotDeg;
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_S))
    {
        rotByEachAxis.x -= rotDeg;
    }
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_A))
    {
        rotByEachAxis.y += rotDeg;
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_D))
    {
        rotByEachAxis.y -= rotDeg;
    }
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_Q))
    {
        rotByEachAxis.z += rotDeg;
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_E))
    {
        rotByEachAxis.z -= rotDeg;
    }
    
    
    if(glm::length(rotByEachAxis) > 0.0f)
    {
        rot = glm::rotate(rot,glm::radians<float>(rotByEachAxis.x),glm::vec3(1,0,0));
        rot = glm::rotate(rot,glm::radians<float>(rotByEachAxis.y),glm::vec3(0,1,0));
//        rot = glm::rotate(rot,glm::radians<float>(rotByEachAxis.z),glm::vec3(0,0,1));
        
//        rot = rot * mat;
//        rot = mat * rot;
        
        glm::vec4 from = glm::vec4(camComp->LookDir(),0.0);
        glm::vec4 to = from * rot;
        
        fl::Log::Info(rot);
        
//        to = glm::normalize(to);
        
        camComp->SetLookDir(to);
//        glm::vec3 newLookDir = glm::vec4(camComp->LookDir(),0.0) * rot;
//        camComp->SetLookDir(newLookDir);
        printf("xx\n");
    }
}

}
