#version 330 core
in vec2 fTexCoord;

uniform sampler2D character;
uniform vec4 color;

out vec4 glFragColor;

void main()
{
    //glFragColor = vec4(color.xyz,  texture(character, fTexCoord).r);
    glFragColor = vec4(color.xyz, color.a * texture(character, fTexCoord).r);
    //glFragColor = texture(_texture, fTexCoord).r;
    //glFragColor = vec4(1.0, 0.0, 0.0, 1.0) * vec4(1.0, 1.0, 1.0, );
}