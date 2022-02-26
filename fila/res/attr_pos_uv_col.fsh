#version 330 core
out vec4 FragColor;

in vec2 vUV;
in vec3 vColor;

void main()
{
    FragColor = vec4(vColor.r,vColor.g,vColor.b,1.0);
}
