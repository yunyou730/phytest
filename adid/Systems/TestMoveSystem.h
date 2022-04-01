#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class TestMoveSystem : public fl::System,public fl::ISysUpdate
{
public:
    TestMoveSystem(fl::Framework* framework);
    
    virtual void Update() override;
    
protected:
    fl::WCKeyboardInput* _keyboardInput = nullptr;
};

}

