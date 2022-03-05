#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class CameraCtrlSystem : public fl::System,public fl::ISysUpdate
{
public:
    CameraCtrlSystem(fl::Framework* framework);
    
    virtual void Update() override;
    
protected:
    void DumpKeyboardState();
    void HandleCameraMove(fl::Entity* camEntity);
    
protected:
    fl::WCKeyboardInput* _keyboardInput = nullptr;
};

}

