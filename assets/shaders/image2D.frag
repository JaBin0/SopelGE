#version 330 core
in vec2 fTex;

out vec4 glFragColor;

uniform sampler2D image;

void main() {
    glFragColor = texture(image, fTex);
    //glFragColor = vec4(0.6, 0.8, 0.2, 1.0);
}