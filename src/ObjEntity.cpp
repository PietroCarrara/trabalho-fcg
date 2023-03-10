#include "ObjEntity.h"
#include "GraphicsManager.hpp"

#include <cstdio>
#include <iostream>

#include "stb_image.h"

ObjEntity::ObjEntity(const char* filename, const char* textureFilename)
{

    const char* basepath = NULL;
    const bool triangulate = true;

    printf("Carregando objetos do arquivo \"%s\"...\n", filename);

    // Se basepath == NULL, então setamos basepath como o dirname do
    // filename, para que os arquivos MTL sejam corretamente carregados caso
    // estejam no mesmo diretório dos arquivos OBJ.
    std::string fullpath(filename);
    std::string dirname;
    if (basepath == NULL)
    {
        auto i = fullpath.find_last_of("/");
        if (i != std::string::npos)
        {
            dirname = fullpath.substr(0, i+1);
            basepath = dirname.c_str();
        }
    }

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, basepath, triangulate);

    if (!err.empty())
        fprintf(stderr, "\n%s\n", err.c_str());

    if (!warn.empty()) {
        fprintf(stderr, "\n%s\n", warn.c_str());
    }

    if (!ret)
        throw std::runtime_error("Erro ao carregar modelo.");

    for (size_t shape = 0; shape < shapes.size(); ++shape)
    {
        if (shapes[shape].name.empty())
        {
            fprintf(stderr,
                    "*********************************************\n"
                    "Erro: Objeto sem nome dentro do arquivo '%s'.\n"
                    "Veja https://www.inf.ufrgs.br/~eslgastal/fcg-faq-etc.html#Modelos-3D-no-formato-OBJ .\n"
                    "*********************************************\n",
                filename);
            throw std::runtime_error("Objeto sem nome.");
        }
        printf("- Objeto '%s'\n", shapes[shape].name.c_str());
    }

    printf("OK.\n");

    this->computeNormals();
    this->buildTriangles();
    this->loadTexture(textureFilename);
}

void ObjEntity::update(float deltaTime) {

}

void ObjEntity::draw(Camera* c) {
    glm::mat4 model =
      Matrix_Translate(this->position.x, this->position.y, this->position.z) *
      Matrix_Scale(this->scale.x, this->scale.y, this->scale.z) *
      Matrix_Rotate_X(this->rotation.x) *
      Matrix_Rotate_Y(this->rotation.y) *
      Matrix_Rotate_Z(this->rotation.z);

    for (uint i = 0; i < this->vboIDs.size(); i++) {
        GraphicsManager::DrawElements(model, c, this->bboxMin[i], this->bboxMax[i], this->textureID, this->vboIDs[i], GL_TRIANGLES, this->indexCount[i], GL_UNSIGNED_INT, (void*)(this->firstIndex[i]*sizeof(GLuint)));
    }

}

void ObjEntity::computeNormals() {
    if ( !this->attrib.normals.empty() )
        return;

    // Primeiro computamos as normais para todos os TRIÂNGULOS.
    // Segundo, computamos as normais dos VÉRTICES através do método proposto
    // por Gouraud, onde a normal de cada vértice vai ser a média das normais de
    // todas as faces que compartilham este vértice.

    size_t num_vertices = this->attrib.vertices.size() / 3;

    std::vector<int> num_triangles_per_vertex(num_vertices, 0);
    std::vector<glm::vec4> vertex_normals(num_vertices, glm::vec4(0.0f,0.0f,0.0f,0.0f));

    for (size_t shape = 0; shape < this->shapes.size(); ++shape)
    {
        size_t num_triangles = this->shapes[shape].mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(this->shapes[shape].mesh.num_face_vertices[triangle] == 3);

            glm::vec4  vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = this->shapes[shape].mesh.indices[3*triangle + vertex];
                const float vx = this->attrib.vertices[3*idx.vertex_index + 0];
                const float vy = this->attrib.vertices[3*idx.vertex_index + 1];
                const float vz = this->attrib.vertices[3*idx.vertex_index + 2];
                vertices[vertex] = glm::vec4(vx,vy,vz,1.0);
            }

            const glm::vec4  a = vertices[0];
            const glm::vec4  b = vertices[1];
            const glm::vec4  c = vertices[2];

            const glm::vec4 n = glm::normalize(crossproduct(b - a, c - a));

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = this->shapes[shape].mesh.indices[3*triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] += n;
                this->shapes[shape].mesh.indices[3*triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    this->attrib.normals.resize( 3*num_vertices );

    for (size_t i = 0; i < vertex_normals.size(); ++i)
    {
        glm::vec4 n = vertex_normals[i] / (float)num_triangles_per_vertex[i];
        n /= norm(n);
        this->attrib.normals[3*i + 0] = n.x;
        this->attrib.normals[3*i + 1] = n.y;
        this->attrib.normals[3*i + 2] = n.z;
    }
}

void ObjEntity::buildTriangles() {

    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    std::vector<GLuint> indices;
    std::vector<float>  model_coefficients;
    std::vector<float>  normal_coefficients;
    std::vector<float>  texture_coefficients;
    std::vector<int> texture_index;

    const float minval = std::numeric_limits<float>::min();
    const float maxval = std::numeric_limits<float>::max();


    for (size_t shape = 0; shape < this->shapes.size(); ++shape)
    {
        size_t first_index = indices.size();
        size_t num_triangles = this->shapes[shape].mesh.num_face_vertices.size();


        glm::vec3 bboxMin = glm::vec3(maxval,maxval,maxval);
        glm::vec3 bboxMax = glm::vec3(minval,minval,minval);

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(this->shapes[shape].mesh.num_face_vertices[triangle] == 3);

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = this->shapes[shape].mesh.indices[3*triangle + vertex];

                indices.push_back(first_index + 3*triangle + vertex);

                const float vx = this->attrib.vertices[3*idx.vertex_index + 0];
                const float vy = this->attrib.vertices[3*idx.vertex_index + 1];
                const float vz = this->attrib.vertices[3*idx.vertex_index + 2];
                //printf("tri %d vert %d = (%.2f, %.2f, %.2f)\n", (int)triangle, (int)vertex, vx, vy, vz);
                model_coefficients.push_back( vx ); // X
                model_coefficients.push_back( vy ); // Y
                model_coefficients.push_back( vz ); // Z
                model_coefficients.push_back( 1.0f ); // W


                bboxMin.x = std::min(bboxMin.x, vx);
                bboxMin.y = std::min(bboxMin.y, vy);
                bboxMin.z = std::min(bboxMin.z, vz);
                bboxMax.x = std::max(bboxMax.x, vx);
                bboxMax.y = std::max(bboxMax.y, vy);
                bboxMax.z = std::max(bboxMax.z, vz);


                // Inspecionando o código da tinyobjloader, o aluno Bernardo
                // Sulzbach (2017/1) apontou que a maneira correta de testar se
                // existem normais e coordenadas de textura no ObjModel é
                // comparando se o índice retornado é -1. Fazemos isso abaixo.

                if ( idx.normal_index != -1 )
                {
                    const float nx = this->attrib.normals[3*idx.normal_index + 0];
                    const float ny = this->attrib.normals[3*idx.normal_index + 1];
                    const float nz = this->attrib.normals[3*idx.normal_index + 2];
                    normal_coefficients.push_back( nx ); // X
                    normal_coefficients.push_back( ny ); // Y
                    normal_coefficients.push_back( nz ); // Z
                    normal_coefficients.push_back( 0.0f ); // W
                }

                if ( idx.texcoord_index != -1 )
                {
                    const float u = this->attrib.texcoords[2*idx.texcoord_index + 0];
                    const float v = this->attrib.texcoords[2*idx.texcoord_index + 1];
                    texture_coefficients.push_back( u );
                    texture_coefficients.push_back( v );
                }

                // TODO: Get texture index from .obj file
                texture_index.push_back(1);
            }
        }

        size_t last_index = indices.size() - 1;


        this->firstIndex.push_back(first_index); // Primeiro índice
        this->indexCount.push_back(last_index - first_index + 1); // Número de indices
        this->vboIDs.push_back(vertex_array_object_id);
        this->bboxMin.push_back(bboxMin);
        this->bboxMax.push_back(bboxMax);
    }

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint textureIndexBufferID;
    glGenBuffers(1, &textureIndexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, textureIndexBufferID);
    glBufferData(GL_ARRAY_BUFFER, texture_index.size() * sizeof(int), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, texture_index.size() * sizeof(int), texture_index.data());
    location = 4;
    number_of_dimensions = 1;
    glVertexAttribPointer(location, number_of_dimensions, GL_INT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if ( !normal_coefficients.empty() )
    {
        GLuint VBO_normal_coefficients_id;
        glGenBuffers(1, &VBO_normal_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());
        location = 1; // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if ( !texture_coefficients.empty() )
    {
        GLuint VBO_texture_coefficients_id;
        glGenBuffers(1, &VBO_texture_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, texture_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texture_coefficients.size() * sizeof(float), texture_coefficients.data());
        location = 2; // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 2; // vec2 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    // "Ligamos" o buffer. Note que o tipo agora é GL_ELEMENT_ARRAY_BUFFER.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // XXX Errado!
    //

    // "Desligamos" o VAO, evitando assim que operações posteriores venham a
    // alterar o mesmo. Isso evita bugs.
    glBindVertexArray(0);
}

static int loadedTexCount = 0;

void ObjEntity::loadTexture(const char* fname) {
    if (this->materials.size() > 0) {
        const tinyobj::material_t m = this->materials[0];

        std::cout << *(m.diffuse);
    }

    const char* files[] = { fname, "../../assets/objects/firbark.png" };
    const int textureCount = 2;


    for (int i = 0; i < textureCount; i++) {
        const char* filename = files[i];

        printf("Carregando imagem \"%s\"... ", filename);

        // Primeiro fazemos a leitura da imagem do disco
        stbi_set_flip_vertically_on_load(true);
        int width;
        int height;
        int channels;
        unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);

        if ( data == NULL )
        {
            fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
            std::exit(EXIT_FAILURE);
        }

        printf("OK (%dx%d).\n", width, height);

        GLuint texture_id;
        GLuint sampler_id;
        glGenTextures(1, &texture_id);
        glGenSamplers(1, &sampler_id);
        glActiveTexture(GL_TEXTURE0+loadedTexCount);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);

        // Veja slides 95-96 do documento Aula_20_Mapeamento_de_Texturas.pdf
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Parâmetros de amostragem da textura.
        glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Agora enviamos a imagem lida do disco para a GPU
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

        GLuint textureunit = loadedTexCount;
        glActiveTexture(GL_TEXTURE0 + textureunit);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindSampler(textureunit, sampler_id);

        stbi_image_free(data);

        this->textureID.push_back(textureunit);
        loadedTexCount++;
    }
}
