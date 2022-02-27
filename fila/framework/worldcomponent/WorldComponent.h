#pragma once
#include "window.h"

namespace fl {

class WorldComponent
{
public:
    virtual ~WorldComponent() {}
};

class WCGlobalRenderParam : public WorldComponent
{
public:
    LaunchParam launchParam;
};

}
