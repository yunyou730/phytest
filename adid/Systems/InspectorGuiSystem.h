#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace fl
{
class WCDestroy;
}

namespace ad {

class WCEntitySelection;
class InspectorGuiSystem : public fl::System,public fl::ISysGUI
{
public:
    InspectorGuiSystem(fl::Framework* framework);
    virtual void OnGUI() override;
    
protected:
    void RefreshInspector(fl::Entity* entity);
    void ShowAddComponentPart(fl::Entity* entity);
    void DoAddComponent(int index,fl::Entity* entity);
    
protected:
    WCEntitySelection*  _entitySelection = nullptr;
    int     _toAddComponentIndex = 0;
    
    fl::WCDestroy*  _destroy = nullptr;
};

}

