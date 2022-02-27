#version 330 core
layout(location = 0) in vec3 aPos;

//uniform mat4 u_Rot;
//uniform mat4 u_Scale;
//uniform mat4 u_Translate;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec4 pos = vec4(aPos,1.0);
    
//    mat4 model = u_Rot * u_Scale * u_Translate;
    
    pos = pos * u_Model * u_View * u_Projection;
    
//    pos = u_Projection * u_View * u_Model * pos;
    
    gl_Position = pos;//vec4(aPos.x,aPos.y,aPos.z,1.0);
}
