#include "PrimitiveComponent.h"
#include <cassert>
#include "PrimObject.h"

namespace fl
{

PrimitiveComponent::PrimitiveComponent(EPrimitiveType primType)
{
    _primObject = PrimitiveManager::Instance()->GetPrimObject(primType);
}

GLuint PrimitiveComponent::GetVAO() const
{
    return _primObject->GetVAO();
}

bool PrimitiveComponent::IsEBOEnable() const
{
    return _primObject->IsEBOEnable();
}

int PrimitiveComponent::GetVerticesCount() const
{
    return _primObject->GetVerticesCount();
}

int PrimitiveComponent::GetIndicesCount() const
{
    return _primObject->GetIndicesCount();
}

}

