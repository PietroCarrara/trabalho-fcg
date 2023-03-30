#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 vertexColor;
in vec4 positionWorld;
in vec4 normal;
in vec2 texCoord;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 viewVec;

uniform vec3 bboxMin;
uniform vec3 bboxMax;

uniform float time;
uniform float noisiness;

uniform sampler2D colorTexture;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

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
    color.rgb = (1-inside) * (lambert_diffuse_term + ambient_term + phong_specular_term) +
                (inside) * ambient_term;

    // "Fog", maximum distance to illuminate things
    float d = distance(p, camera_position);
    float distanceNormalized = min(1, d / 60);
    color.rgb *= 1 - easeInOutSine(distanceNormalized);

    // Cor final com correção gamma, considerando monitor sRGB.
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
    // Slender noise
    color.rgb = mix(color.rgb, vec3(random(vec2((vertexColor.xz + texCoord.xy) * time))), noisiness);
    color.a = 1;
}



