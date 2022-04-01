#include "Phy2DSystem.h"
#include "Framework.h"
#include "application.h"
#include "Phy2DComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

#include "Phy2dFunc.h"
#include "RenderFunc.h"

namespace fl
{

Phy2DSystem::Phy2DSystem(Framework* framework)
    :System(framework)
{
    
}

void Phy2DSystem::Prepare(const LaunchParam& launchParam)
{
    _compSetWithPhy2d.insert(TransformComponent::ClsName());
    _compSetWithPhy2d.insert(Phy2DComponent::ClsName());
    
    _phy2dSettings = GetFramework()->GetWorldComponent<WCPhy2DSettings>();
    _destroy = GetFramework()->GetWorldComponent<WCDestroy>();
    
    _world = new b2World(_phy2dSettings->_gravity);
    _shaderManager = GetFramework()->GetApp()->GetShaderManager();
}

void Phy2DSystem::Update()
{
    CheckAndCreateBody();
    ProcessTickRate();
    SyncPhyPropToTransform();
}

void Phy2DSystem::LateUpdate()
{
    for(auto it : _destroy->_toDestroy)
    {
        int entityId = it;
        Entity* entity = GetFramework()->GetEntity(entityId);
        if(entity != nullptr)
        {
            HandleDestroyedEntity(entity);
        }
    }
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
    std::vector<fl::Entity*> entities = GetFramework()->QueryEntityWithCompSet(_compSetWithPhy2d);
    
    for(auto it = entities.begin();it != entities.end();it++)
    {
        Phy2DComponent* phy2dComp = (*it)->GetComponent<Phy2DComponent>();
        if(!phy2dComp->HasBodyCreated())
        {
            TransformComponent* transform = (*it)->GetComponent<TransformComponent>();
            phy2dComp->CreateBody(_world,transform->GetPos());
        }
    }
}

void Phy2DSystem::SyncPhyPropToTransform()
{
    std::vector<fl::Entity*> entities = GetFramework()->QueryEntityWithCompSet(_compSetWithPhy2d);
    for(auto it = entities.begin();it != entities.end();it++)
    {
        Entity* entity = *it;
        Phy2dFunc::SyncPhyAndTransform(_phy2dSettings,entity);
    }
}

void Phy2DSystem::Renderer()
{
    std::vector<Entity*> cameraEntities = RenderUtil::GetCameraEntities(GetFramework());
    std::vector<fl::Entity*> toRenderEntities = GetFramework()->QueryEntityWithCompSet(_compSetWithPhy2d);
    
    // Each camera renders each entity.
    for(auto camIt = cameraEntities.begin();camIt != cameraEntities.end();camIt++)
    {
        auto camComp = (*camIt)->GetComponent<CameraComponent>();
        for(auto it = toRenderEntities.begin();it != toRenderEntities.end();it++)
        {
            Entity* entity = *it;
            if(camComp->IsDrawDebugInfo())
            {
                Phy2dFunc::DrawDebugWire(_shaderManager,_phy2dSettings,entity->GetComponent<Phy2DComponent>(),camComp);
            }
        }
    }
}

void Phy2DSystem::HandleDestroyedEntity(Entity* entity)
{
    auto phy2dComp = entity->GetComponent<Phy2DComponent>();
    if(phy2dComp != nullptr)
    {
        auto body = phy2dComp->GetBody();
        _world->DestroyBody(body);
    }
}

}
