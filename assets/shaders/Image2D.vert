#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vTex;

out vec2 fTex;

uniform mat4 projection;

void main () {
    gl_Position = projection * vec4(vPos.xy, 0.1, 1.0);
    fTex = vTex;
}