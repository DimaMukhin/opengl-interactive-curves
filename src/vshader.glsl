#version 150

in vec4 vPosition;

uniform mat4 model, view, projection;

void main()
{
    gl_Position = projection * view * model * vPosition;
}

