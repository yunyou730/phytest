#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class HierarychyGUISystem : public fl::System,public fl::ISysGUI
{
public:
    HierarychyGUISystem(fl::Framework* framework);

    virtual void OnGUI() override;
};

}

