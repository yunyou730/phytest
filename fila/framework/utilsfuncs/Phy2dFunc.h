#pragma once

#include "Framework.h"
#include <set>
#include <string>

#include "Entity.h"
#include "WorldComponent.h"
#include "ShaderManager.h"

namespace fl {

class Phy2DComponent;
class CameraComponent;
class Phy2dFunc
{
public:
    static void SyncPhyAndTransform(const WCPhy2DSettings* phy2dSettings, Entity* entity);
    static void DrawDebugWire(ShaderManager* shaderManager,const WCPhy2DSettings* phy2dSettings,Phy2DComponent* phy2d,CameraComponent* cam);
};

}
