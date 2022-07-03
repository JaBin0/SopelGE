#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNorm;
layout(location = 3) in vec3 vTangent;


out vec3 fPos;
out vec2 fTexCoord;
out vec3 fNorm;
out mat3 fTbn;


out vec3 fn;
out vec3 ft;
out vec3 fb;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    fPos = vec3(model * vec4(vPos.xyz, 1.0));
    fNorm = normalize(mat3(transpose(inverse(model))) * vNorm);
    //fNorm = vNorm;
    fTexCoord = vTexCoord;
    vec3 n = normalize(mat3(transpose(inverse(model))) * vNorm);
    vec3 t = normalize(mat3(transpose(inverse(model))) * vTangent);
    t = normalize(t - dot(t, n) * n);
    

    //vec3 B = cross(N, T);
    vec3 b = cross(t, n);

    //vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
    
    mat3 fTbn = mat3(t, b, n);
    fn = n;
    ft = t;
    fb = b;
    //transpose(mat3(t, b, n));//

}