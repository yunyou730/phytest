#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class WCPreviewMode;
class PreviewModeGuiSystem : public fl::System,public fl::ISysGUI
{
public:
    PreviewModeGuiSystem(fl::Framework* framework);
    virtual void OnGUI() override;
    
protected:
    bool    _bOpen = true;
    
    WCPreviewMode*  _previewMode = nullptr;
};

}

