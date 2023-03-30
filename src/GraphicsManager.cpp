#include "GraphicsManager.hpp"

#include <glcommon.h>

#include "stb_image.h"

static GLuint LoadShadersFromFiles(const char*, const char*);
static GLuint LoadShader_Vertex(const char*);
static GLuint LoadShader_Fragment(const char*);
static void LoadShader(const char*, GLuint);
static GLuint CreateGpuProgram(GLuint, GLuint);

float GraphicsManager::screenRatio = 1;

glm::mat4 GraphicsManager::perspectiveProjection = Matrix_Perspective(GraphicsManager::fov, 1, GraphicsManager::nearPlane, GraphicsManager::farPlane);

float GraphicsManager::fov = 3.141592f / 3.0f;
float GraphicsManager::nearPlane = -0.1;
float GraphicsManager::farPlane = -60.0;

GLuint GraphicsManager::shaderID = -1;
GLuint GraphicsManager::skyboxShaderID = -1;
GLuint GraphicsManager::gouraudID = -1;

GLint GraphicsManager::modelUniform = -1;
GLint GraphicsManager::viewUniform = -1;
GLint GraphicsManager::projectionUniform = -1;
GLint GraphicsManager::viewVecUniform = -1;
GLint GraphicsManager::bboxMinUniform = -1;
GLint GraphicsManager::bboxMaxUniform = -1;
GLint GraphicsManager::colorTextureUniform = -1;
GLint GraphicsManager::timeUniform = -1;
GLint GraphicsManager::noisinessUniform = -1;

GLint GraphicsManager::skyboxViewUniform = -1;
GLint GraphicsManager::skyboxProjectionUniform = -1;
GLint GraphicsManager::skyboxColorTextureUniform = -1;
GLint GraphicsManager::skyboxTimeUniform = -1;
GLint GraphicsManager::skyboxNoisinessUniform = -1;

GLint GraphicsManager::gouraudModel = -1;
GLint GraphicsManager::gouraudView = -1;
GLint GraphicsManager::gouraudProjection = -1;
GLint GraphicsManager::gouraudViewVec = -1;
GLint GraphicsManager::gouraudColorTexture = -1;
GLint GraphicsManager::gouraudTime = 1;
GLint GraphicsManager::gouraudNoisiness = 1;

void GraphicsManager::init() {
  shaderID = LoadShadersFromFiles("../../src/shader_vertex.glsl", "../../src/shader_fragment.glsl");
  skyboxShaderID = LoadShadersFromFiles("../../src/skybox.vert.glsl", "../../src/skybox.frag.glsl");
  gouraudID = LoadShadersFromFiles("../../src/gouraud.vert.glsl", "../../src/gouraud.frag.glsl");

  modelUniform = glGetUniformLocation(shaderID, "model");
  viewUniform = glGetUniformLocation(shaderID, "view");
  projectionUniform = glGetUniformLocation(shaderID, "projection");
  viewVecUniform = glGetUniformLocation(shaderID, "viewVec");
  bboxMinUniform = glGetUniformLocation(shaderID, "bboxMin");
  bboxMaxUniform = glGetUniformLocation(shaderID, "bboxMax");
  colorTextureUniform = glGetUniformLocation(shaderID, "colorTexture");
  timeUniform = glGetUniformLocation(shaderID, "time");
  noisinessUniform = glGetUniformLocation(shaderID, "noisiness");

  skyboxViewUniform = glGetUniformLocation(skyboxShaderID, "view");
  skyboxProjectionUniform = glGetUniformLocation(skyboxShaderID, "projection");
  skyboxColorTextureUniform = glGetUniformLocation(skyboxShaderID, "skybox");
  skyboxTimeUniform = glGetUniformLocation(skyboxShaderID, "time");
  skyboxNoisinessUniform = glGetUniformLocation(skyboxShaderID, "noisiness");

  gouraudModel = glGetUniformLocation(gouraudID, "model");
  gouraudView = glGetUniformLocation(gouraudID, "view");
  gouraudProjection = glGetUniformLocation(gouraudID, "projection");
  gouraudViewVec = glGetUniformLocation(gouraudID, "viewVec");
  gouraudColorTexture = glGetUniformLocation(gouraudID, "colorTexture");
  gouraudTime = glGetUniformLocation(gouraudID, "time");
  gouraudNoisiness = glGetUniformLocation(gouraudID, "noisiness");
}

void GraphicsManager::setScreenRatio(float r) {
  screenRatio = r;
  perspectiveProjection = Matrix_Perspective(fov, r, nearPlane, farPlane);
}

void GraphicsManager::setTime(float t) {
  glUseProgram(shaderID);
  glUniform1f(timeUniform, t);

  glUseProgram(skyboxShaderID);
  glUniform1f(skyboxTimeUniform, t);

  glUseProgram(gouraudID);
  glUniform1f(gouraudTime, t);
}

void GraphicsManager::setNoisiness(float n) {
  glUseProgram(shaderID);
  glUniform1f(noisinessUniform, n);

  glUseProgram(skyboxShaderID);
  glUniform1f(skyboxNoisinessUniform, n);

  glUseProgram(gouraudID);
  glUniform1f(gouraudNoisiness, n);
}

void GraphicsManager::DrawElements(glm::mat4 model, Camera* cam, glm::vec3 bboxMin, glm::vec3 bboxMax, GLuint texture, GLuint vertexArrayID, GLenum drawMode, GLsizei elCount, GLenum type, void* firstIndex) {
  glUseProgram(shaderID);

  glBindVertexArray(vertexArrayID);

  glUniformMatrix4fv(modelUniform     , 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewUniform      , 1, GL_FALSE, glm::value_ptr(cam->getMatrix()));
  glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjection));
  glUniform4fv(viewVecUniform, 1, glm::value_ptr(cam->getViewVec()));
  glUniform4fv(bboxMinUniform, 1, glm::value_ptr(bboxMin));
  glUniform4fv(bboxMaxUniform, 1, glm::value_ptr(bboxMax));
  glUniform1i(colorTextureUniform, texture);

  glDrawElements(
      drawMode,
      elCount,
      type,
      firstIndex
  );

  glBindVertexArray(0);
}

void GraphicsManager::DrawElementsGouraud(glm::mat4 model, Camera* cam, glm::vec3 bboxMin, glm::vec3 bboxMax, GLuint texture, GLuint vertexArrayID, GLenum drawMode, GLsizei elCount, GLenum type, void* firstIndex) {
  glUseProgram(gouraudID);

  glBindVertexArray(vertexArrayID);

  glUniformMatrix4fv(gouraudModel     , 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(gouraudView      , 1, GL_FALSE, glm::value_ptr(cam->getMatrix()));
  glUniformMatrix4fv(gouraudProjection, 1, GL_FALSE, glm::value_ptr(perspectiveProjection));
  glUniform4fv(gouraudViewVec, 1, glm::value_ptr(cam->getViewVec()));
  glUniform1i(gouraudColorTexture, texture);

  glDrawElements(
      drawMode,
      elCount,
      type,
      firstIndex
  );

  glBindVertexArray(0);
}

void GraphicsManager::DrawSkybox(Camera* cam, GLuint texture, GLuint vertexArrayID) {
  glUseProgram(skyboxShaderID);
  glDepthMask(GL_FALSE);
  glDisable(GL_CULL_FACE);

  glBindVertexArray(vertexArrayID);
  glUniformMatrix4fv(skyboxViewUniform      , 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(cam->getMatrix()))));
  glUniformMatrix4fv(skyboxProjectionUniform, 1, GL_FALSE, glm::value_ptr(perspectiveProjection));
  glUniform1i(skyboxColorTextureUniform, texture);

  glDrawElements(
    GL_TRIANGLES,
    36,
    GL_UNSIGNED_INT,
    (void*)0
  );
  glBindVertexArray(0);

  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
}

static int loadedTexCount = 0;

GLuint GraphicsManager::loadTexture(std::string filename) {
    printf("Carregando imagem \"%s\"... ", filename.c_str());

    // Primeiro fazemos a leitura da imagem do disco
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if ( data == NULL )
    {
        fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename.c_str());
        std::exit(EXIT_FAILURE);
    }

    printf("OK (%dx%d).\n", width, height);

    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    // Veja slides 95-96 do documento Aula_20_Mapeamento_de_Texturas.pdf
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S,  GL_REPEAT);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T,  GL_REPEAT);

    // Parâmetros de amostragem da textura.
    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

    loadedTexCount++;
    return textureunit;
}

/**
 * Texture order:
 * - GL_TEXTURE_CUBE_MAP_POSITIVE_X  Right
 * - GL_TEXTURE_CUBE_MAP_NEGATIVE_X  Left
 * - GL_TEXTURE_CUBE_MAP_POSITIVE_Y  Top
 * - GL_TEXTURE_CUBE_MAP_NEGATIVE_Y  Bottom
 * - GL_TEXTURE_CUBE_MAP_POSITIVE_Z  Back
 * - GL_TEXTURE_CUBE_MAP_NEGATIVE_Z  Front
 */
GLuint GraphicsManager::loadCubeMap(std::vector<const char*> filenames) {
    GLuint textureunit = loadedTexCount;
    loadedTexCount++;
    GLuint texture_id;

    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0 + textureunit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(false);
    for (int i = 0; i < 6; i++) {
        const char* filename = filenames[i];
        printf("Carregando imagem \"%s\"... ", filename);

        int width;
        int height;
        int channels;
        unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);
        if ( data == NULL )
        {
            fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
            std::exit(EXIT_FAILURE);
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);

        printf("OK (%dx%d).\n", width, height);
    }

    return textureunit;
}

static GLuint LoadShader_Vertex(const char* filename)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    LoadShader(filename, vertex_shader_id);
    return vertex_shader_id;
}

static GLuint LoadShader_Fragment(const char* filename)
{
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(filename, fragment_shader_id);
    return fragment_shader_id;
}

static void LoadShader(const char* filename, GLuint shader_id)
{
    std::ifstream file;
    try {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    } catch ( std::exception& e ) {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);
    glCompileShader(shader_id);

    // Verificamos se ocorreu algum erro ou "warning" durante a compilação
    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);
    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);
    if ( log_length != 0 )
    {
        std::string  output;

        if ( !compiled_ok )
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        fprintf(stderr, "%s", output.c_str());
    }
    delete [] log;
}

static GLuint LoadShadersFromFiles(const char* vertex, const char* frag)
{
    GLuint vertex_shader_id = LoadShader_Vertex(vertex);
    GLuint fragment_shader_id = LoadShader_Fragment(frag);

    return CreateGpuProgram(vertex_shader_id, fragment_shader_id);
}

static GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    GLuint program_id = glCreateProgram();

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);
    if ( linked_ok == GL_FALSE )
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* log = new GLchar[log_length];
        glGetProgramInfoLog(program_id, log_length, &log_length, log);
        std::string output;
        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "\n== End of link log\n";
        delete [] log;
        fprintf(stderr, "%s", output.c_str());
    }

    return program_id;
}
