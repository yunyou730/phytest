#pragma once
#include "application.h"
#include "fila.h"

#include "WorldComponent.h"

namespace ad {


class WCEntitySelection : public fl::WorldComponent
{
public:
    static std::string ClsName() { return "WCEntitySelection"; }
    unsigned int selectedEntityID = 0;
};


}

