#include "TestMoveSystem.h"

#include "fila.h"
#include "Entity.h"
#include <vector>

#include "TransformComponent.h"
#include "CameraComponent.h"

namespace ad {

TestMoveSystem::TestMoveSystem(fl::Framework* framework)
    :System(framework)
{
    _keyboardInput = _framework->GetWorldComponent<fl::WCKeyboardInput>();
}

void TestMoveSystem::Update()
{
    const float moveSpeed = 3.0;
    float dt = GetFramework()->GetApp()->GetDeltaTime();
    
    
    auto entity = GetFramework()->GetEntity(2);
    if(entity != nullptr)
    {
        auto transform = entity->GetComponent<fl::TransformComponent>();
        
        glm::vec3 movement(0.0);
        if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_Q))
        {
            movement += glm::vec3(1.0,0,0);
        }
        if(_keyboardInput->IsKeyPressed(fl::EInputKey::KEY_E))
        {
            movement += glm::vec3(-1.0,0,0);
        }
        
        if(glm::length(movement) > 0.0)
        {
            movement = glm::normalize(movement) * glm::vec3(moveSpeed) * dt;
            transform->SetPosition(transform->GetPos() + movement);
        }
    }
}

}
