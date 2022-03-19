#pragma once
#include "application.h"
#include "fila.h"

namespace fl
{
class Entity;
class Component;
}

namespace ad {

class ComponentFactory
{
public:
    static fl::Component* CreateComponent(const char* compName,fl::Entity* entity);
};

}

