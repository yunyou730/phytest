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

    
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(CameraComponent));
    compSet.insert(CLASS_NAME(TransformComponent));
    std::vector<fl::Entity*> entities = GetFramework()->QueryEntityWithCompSet(compSet);
    
    for(auto it = entities.begin();it != entities.end();it++)
    {
        HandleCameraMove(*it);
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

void CameraCtrlSystem::HandleCameraMove(fl::Entity* camEntity)
{
    auto transform = camEntity->GetComponent<fl::TransformComponent>(CLASS_NAME(TransformComponent));
    
    auto camComp = camEntity->GetComponent<fl::CameraComponent>(CLASS_NAME(CameraComponent));
    
    
    float distance = camComp->MoveSpeed() * _framework->GetApp()->GetDeltaTime();
    glm::vec3 direction(0.0);
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_UP))
    {
        direction.y += 1;
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_DOWN))
    {
        direction.y -= 1;
    }
    
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_LEFT))
    {
        direction.x -= 1;
    }
    if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_RIGHT))
    {
        direction.x += 1;
    }
    if(glm::length(direction) > 0)
    {
        direction = glm::normalize(direction);
        transform->SetPosition(transform->GetPos() + direction * distance);
    }
}

}
