#include "Phy2DSystem.h"
#include "Framework.h"
#include "application.h"
#include "Phy2DComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

#include "Phy2dFunc.h"

namespace fl
{

Phy2DSystem::Phy2DSystem(Framework* framework)
    :System(framework)
{

}

void Phy2DSystem::Prepare(const LaunchParam& launchParam)
{
    _phy2dSettings = GetFramework()->GetWorldComponent<WCPhy2DSettings>();
    _world = new b2World(_phy2dSettings->_gravity);
}

void Phy2DSystem::Update()
{
    CheckAndCreateBody();
    ProcessTickRate();
    SyncPhyPropToTransform();
}

void Phy2DSystem::ProcessTickRate()
{
    float dt = GetFramework()->GetApp()->GetDeltaTime();
    _timeCounter += dt;
    
    int tickTimes = (int)(_timeCounter / _phy2dSettings->TimeStep());
    for(int tickIndex = 0;tickIndex < tickTimes;tickIndex++)
    {
        OnPhyTick();
    }
    _timeCounter -= _phy2dSettings->TimeStep() * tickTimes;
}

void Phy2DSystem::OnPhyTick()
{
    _world->Step(_phy2dSettings->TimeStep(), _phy2dSettings->_velocityIterations, _phy2dSettings->_positionIterations);
}

void Phy2DSystem::CheckAndCreateBody()
{
    std::set<std::string> compSet;
    compSet.insert(TransformComponent::ClsName());
    compSet.insert(Phy2DComponent::ClsName());
    
    std::vector<fl::Entity*> entities = GetFramework()->QueryEntityWithCompSet(compSet);
    
    for(auto it = entities.begin();it != entities.end();it++)
    {
        Phy2DComponent* phy2dComp = (*it)->GetComponent<Phy2DComponent>();
        if(!phy2dComp->HasBodyCreated())
        {
            TransformComponent* transform = (*it)->GetComponent<TransformComponent>();
            
            phy2dComp->CreateBody(_world,transform->GetPos());
            // @miao @todo
            // refresh renderer

        }
    }
}

void Phy2DSystem::SyncPhyPropToTransform()
{
    std::set<std::string> compSet;
    compSet.insert(TransformComponent::ClsName());
    compSet.insert(Phy2DComponent::ClsName());
    
    std::vector<fl::Entity*> entities = GetFramework()->QueryEntityWithCompSet(compSet);
    for(auto it = entities.begin();it != entities.end();it++)
    {
        Entity* entity = *it;
        Phy2dFunc::SyncPhyAndTransform(_phy2dSettings,entity);
    }
}

}
