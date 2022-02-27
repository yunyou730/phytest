#version 330 core
layout(location = 0) in vec3 aPos;

layout(location = 1) in mat4 aModel;
layout(location = 2) in mat4 aView;
layout(location = 3) in mat4 aProjection;

void main()
{
    
    
    gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
}
