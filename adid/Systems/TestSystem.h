#pragma once
#include "application.h"
#include "System.h"

#include "fila.h"

namespace ad {

class TestSystem : public fl::System,public fl::ISysUpdate
{
public:
    TestSystem(fl::Framework* framework);
    virtual void Update() override;
};

}

