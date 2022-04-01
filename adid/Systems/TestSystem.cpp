#include "TestSystem.h"

#include "fila.h"
#include "Entity.h"
#include <vector>

#include "TransformComponent.h"
#include "CameraComponent.h"

namespace ad {

TestSystem::TestSystem(fl::Framework* framework)
    :System(framework)
{
    
}

void TestSystem::Update()
{
//    DumpKeyboardState();
 
    float dt = _framework->GetApp()->GetDeltaTime();
    
    auto entity = GetFramework()->GetEntity(2);
    if(entity != nullptr)
    {
        auto trans = entity->GetComponent<fl::TransformComponent>();
        float deg = trans->_rotByEachAxis.z;
        deg += dt * 90.f;
        
        trans->SetPosition(glm::vec3(-1,2,0));
        trans->SetRotationZ(deg);
    }
}


}
