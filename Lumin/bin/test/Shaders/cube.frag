#version 450 core

uniform sampler2D uTexture;

in vec2 TexCoords;

out vec4 out_Color;

void main()
{ 
    out_Color = texture(uTexture, TexCoords);
}