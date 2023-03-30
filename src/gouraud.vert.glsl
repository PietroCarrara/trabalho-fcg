#version 330 core

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;
layout (location = 3) in vec4 color_coefficients;

out vec4 vertexColor;
out vec4 positionWorld;
out vec4 normal;
out vec2 texCoord;

uniform float time;
uniform float noisiness;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 viewVec;

uniform sampler2D colorTexture;

// FONTE: https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43757.441);
}

// FONTE: https://easings.net/#easeInOutSine
float easeInOutSine(float x) {
  return -(cos(3.1415 * x) - 1) / 2;

}

void main()
{
    gl_Position = projection * view * model * model_coefficients;
    vertexColor = color_coefficients;

    positionWorld = model * model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    texCoord = texture_coefficients;

    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = positionWorld;

    float spotAngle = radians(30.0);

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(camera_position - p);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + 2*n*(dot(n, l));

    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong


    Kd = texture(colorTexture, texCoord).rgb;
    Ks = vec3(0.8, 0.8, 0.8);
    Ka = Kd * 0.05;
    q = 32;

    // Espectro da fonte de iluminação
    vec3 I = vec3(1, 1, 1);
    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2);

    vec3 lambert_diffuse_term = Kd*I*max(0, dot(n, l));
    vec3 ambient_term = Ka*Ia;
    vec3 phong_specular_term  = Ks*I*pow(max(0, dot(r, v)), q);

    float beta = dot(-l, viewVec);
    int inside = int(beta <= cos(spotAngle));

    // Illumination
    vertexColor.rgb = (1-inside) * (lambert_diffuse_term + ambient_term + phong_specular_term) +
                (inside) * ambient_term;

    // "Fog", maximum distance to illuminate things
    float d = distance(p, camera_position);
    float distanceNormalized = min(1, d / 60);
    vertexColor.rgb *= 1 - easeInOutSine(distanceNormalized);

    // Cor final com correção gamma, considerando monitor sRGB.
    vertexColor.rgb = pow(vertexColor.rgb, vec3(1.0,1.0,1.0)/2.2);
    // Slender noise
    vertexColor.rgb = mix(vertexColor.rgb, vec3(random(vec2((texCoord.xy) * time))), noisiness);
    vertexColor.a = 1;
}

