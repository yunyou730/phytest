#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class WCEntitySelection;
class InspectorGuiSystem : public fl::System,public fl::ISysGUI
{
public:
    InspectorGuiSystem(fl::Framework* framework);
    virtual void OnGUI() override;
    
protected:
    void RefreshInspector(fl::Entity* entity);
    
protected:
    WCEntitySelection*  _entitySelection = nullptr;
};

}

