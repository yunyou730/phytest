#include "DestroySystem.h"
#include "WorldComponent.h"

#include "Framework.h"

namespace fl {

DestroySystem::DestroySystem(Framework* framework)
    :System(framework)
{

}

void DestroySystem::Prepare(const LaunchParam& launchParam)
{
    _destroy = GetFramework()->GetWorldComponent<WCDestroy>();
}

void DestroySystem::LateUpdate()
{
    for(auto it : _destroy->_toDestroy)
    {
        int entityId = it;
        GetFramework()->DestroyEntity(entityId);
    }
    _destroy->CleanDestroyList();
}


}
