#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class DebugGuiSystem : public fl::System,public fl::ISysGUI
{
public:
    DebugGuiSystem(fl::Framework* framework);
    virtual void OnGUI() override;

protected:
    void ShowOverlay(bool* bOpen);
    void DoShowDebugInfo();
    
protected:
    bool _bOpen = false;
};

}

