#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float movementx;
uniform float movementy;
void main()
{
    vec3 modifiedPos = aPos;
    modifiedPos.x += movementx;
    modifiedPos.y += movementy;
    gl_Position = vec4(modifiedPos, 1.0);
    ourColor = aColor;
}