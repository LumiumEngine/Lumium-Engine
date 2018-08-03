#version 450 core

uniform sampler2DArray uTexture;
uniform int imageIndex;

in vec2 TexCoords;

out vec4 out_Color;

void main()
{ 
    out_Color = texture(uTexture, vec3(TexCoords, imageIndex));
}