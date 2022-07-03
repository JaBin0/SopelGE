#version 330 core
in vec3 fPos;
in vec2 fTexCoord;
in vec3 fNorm;
in mat3 fTbn;

in vec3 fn;
in vec3 ft;
in vec3 fb;

out vec4 glFragColor;

uniform vec4 baseColor;
uniform uvec2 isTextured;
uniform vec2 textureScale;
uniform sampler2D image;
uniform sampler2D normalMap;
uniform float time; 


void main() {
    vec4 light_color =  vec4(1.0, 1.0, 1.0, 1.0);
    vec3 lightPostion = vec3 (10.0 * sin(time), 2.0, 10.0 * cos(time));//vec3(1.0, 3.0, 1.0);
    float ambient_strength = 0.1;
    vec4 color;
    vec3 nromals = normalize(fNorm);
    if(isTextured.x == 1u) {
        color = texture(image, vec2(fTexCoord.x * textureScale.x, fTexCoord.y * textureScale.y));
        if(isTextured.y == 1u) {
            //normalMap = texture(normalMap, vec2(fTexCoord.x * textureScale.x, fTexCoord.y * textureScale.y)).rgb;
            vec3 normalMap = texture(normalMap, fTexCoord * textureScale).rgb;
            normalMap = (2.0 * normalMap - vec3(1.0)); 
            mat3 tbn = mat3(ft, fb, fn);
            nromals = normalize(tbn * normalMap); 
        }
    }
    else {
        color = baseColor;
    }
    
    vec3 light_direction = normalize(lightPostion - fPos);
    float diffuse = max(dot(nromals, light_direction), 0.0);

    vec3 ambient_light = ambient_strength * light_color.rgb;
    vec3 diffuse_light = diffuse * light_color.rgb;
    vec3 light = ambient_light + diffuse_light;
    // vec3 norm1 = (fNorm + 1.0) / 2.0;
    vec3 norm2 = (fb + 1.0) / 2.0;
    //glFragColor = vec4(fn, 1.0);//vec4(light * color.rgb, 1.0);+
    glFragColor = vec4(light * color.rgb, 1.0);
}

/*    vec3 Normal = normalize(Normal0);
    vec3 Tangent = normalize(Tangent0);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = texture(gNormalMap, TexCoord0).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;*/