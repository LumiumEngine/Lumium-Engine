#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 UV;

out vec2 TexCoords;

uniform mat4 Model;

void main()
{
    gl_Position = Model * vec4(Position, 1.0);
    TexCoords = UV;
}