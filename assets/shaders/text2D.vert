#version 330 core
layout(location = 0) in vec2 vPos;
layout(location = 1) in vec2 vTexCoord;

out vec2 fTexCoord;

uniform mat4 ortho;

void main() {
    gl_Position = ortho * vec4(vPos, 0.0, 1.0);
    fTexCoord = vTexCoord;
}