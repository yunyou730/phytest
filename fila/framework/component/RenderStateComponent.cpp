#include "RenderStateComponent.h"
#include <glad/glad.h>

namespace fl {
GLuint RenderStateComponent::GetPrimitiveType() const
{
    // @temp
    return GL_TRIANGLES;
}

}
