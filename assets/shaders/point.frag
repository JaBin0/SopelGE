#version 330 core
out vec4 glFragColor;

uniform vec2 center;
uniform float size;
uniform vec4 color;

void main() {
    vec2 pos = (center - gl_FragCoord.xy);
    float distance_squared = dot(pos, pos);
    gl_FragColor = (distance_squared < (size * size)) 
        ? vec4(color)
        : vec4(1.0, 1.0, 1.0, 0.0);
}