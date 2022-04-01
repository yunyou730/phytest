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


enum class EPreviewMode
{
    Free,
    Playing,
    
    Max
};

class WCPreviewMode : public fl::WorldComponent
{
public:
    static std::string ClsName() { return "WCPreviewMode"; }
    
    void SwitchPreviewMode();
    
    EPreviewMode   _previewMode = EPreviewMode::Free;
};

}

