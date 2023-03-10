#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 vertexColor;
in vec4 positionWorld;
in vec4 normal;
in vec2 texCoord;
flat in int textureIndex;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 viewVec;

uniform vec3 bboxMin;
uniform vec3 bboxMax;

uniform sampler2D texture0;
uniform sampler2D texture1;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

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

    // Propriedades espectrais do coelho
    switch(textureIndex) {
    case 0:
        Kd = texture(texture0, texCoord).rgb;
        break;
    case 1:
        Kd = texture(texture1, texCoord).rgb;
        break;
    }
    Ks = vec3(0.8, 0.8, 0.8);
    Ka = Kd / 2;
    q = 32;

    // Espectro da fonte de iluminação
    vec3 I = vec3(1, 1, 1);

    // Espectro da luz ambiente
    vec3 Ia = vec3(0.2);

    // Termo difuso utilizando a lei dos cossenos de Lambert
    vec3 lambert_diffuse_term = Kd*I*max(0, dot(n, l));

    // Termo ambiente
    vec3 ambient_term = Ka*Ia;

    // Termo especular utilizando o modelo de iluminação de Phong
    vec3 phong_specular_term  = Ks*I*pow(max(0, dot(r, v)), q);

    // NOTE: Se você quiser fazer o rendering de objetos transparentes, é
    // necessário:
    // 1) Habilitar a operação de "blending" de OpenGL logo antes de realizar o
    //    desenho dos objetos transparentes, com os comandos abaixo no código C++:
    //      glEnable(GL_BLEND);
    //      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 2) Realizar o desenho de todos objetos transparentes *após* ter desenhado
    //    todos os objetos opacos; e
    // 3) Realizar o desenho de objetos transparentes ordenados de acordo com
    //    suas distâncias para a câmera (desenhando primeiro objetos
    //    transparentes que estão mais longe da câmera).
    // Alpha default = 1 = 100% opaco = 0% transparente
    color.a = 1;

    float beta = dot(-l, viewVec);
    int inside = int(beta <= cos(spotAngle));

    color.rgb = (1-inside) * (lambert_diffuse_term + ambient_term + phong_specular_term) +
                (inside) * ambient_term;


    // color.rgb = lambert_diffuse_term + ambient_term + phong_specular_term;

    // Cor final com correção gamma, considerando monitor sRGB.
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);

    // color = positionWorld;
}



