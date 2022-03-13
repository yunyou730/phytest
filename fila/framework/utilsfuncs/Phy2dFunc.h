#pragma once

#include "Framework.h"
#include <set>
#include <string>

#include "Entity.h"
#include "WorldComponent.h"


namespace fl {

class Phy2dFunc
{
public:
    static void SyncPhyAndTransform(const WCPhy2DSettings* phy2dSettings, Entity* entity);
};

}
