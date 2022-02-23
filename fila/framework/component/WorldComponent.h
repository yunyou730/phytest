#pragma once
#include "HashClass.h"
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
    PrepareParam prepareParam;
};

}
