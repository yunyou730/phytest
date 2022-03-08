#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aColor;

//uniform mat4 u_Rot;
//uniform mat4 u_Scale;
//uniform mat4 u_Translate;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 v_Color;

void main()
{
    vec4 pos = vec4(aPos,1.0);
    pos = pos * u_Model * u_View * u_Projection;
    
    gl_Position = pos;
    
    v_Color = aColor;
    
}
