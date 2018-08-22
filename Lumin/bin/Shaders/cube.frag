#version 450 core

uniform sampler2D uTexture;

in vec2 TexCoords;

out vec4 out_Color;

void main()
{
    vec4 texture = texture(uTexture, TexCoords);
    out_Color = vec4(texture.r, texture.r, texture.r, texture.r);
}