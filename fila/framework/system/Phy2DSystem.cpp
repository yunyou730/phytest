#include "Phy2DSystem.h"
#include "Framework.h"
#include "application.h"

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

}
