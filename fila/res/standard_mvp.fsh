#version 330 core
out vec4 FragColor;

in vec3 v_Color;

void main()
{
//    FragColor = vec4(0.4,0.9,0.1,1.0);
    
//    FragColor = vec4(0.9,1.0,0.1,1.0);
    
    FragColor = vec4(v_Color,1.0);
}
