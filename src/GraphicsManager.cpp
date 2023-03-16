#include "GraphicsManager.hpp"

#include <glcommon.h>

static GLuint LoadShadersFromFiles();
static GLuint LoadShader_Vertex(const char*);
static GLuint LoadShader_Fragment(const char*);
static void LoadShader(const char*, GLuint);
static GLuint CreateGpuProgram(GLuint, GLuint);

float GraphicsManager::screenRatio = 1;

glm::mat4 GraphicsManager::perspectiveProjection = Matrix_Perspective(GraphicsManager::fov, 1, GraphicsManager::nearPlane, GraphicsManager::farPlane);

float GraphicsManager::fov = 3.141592f / 3.0f;
float GraphicsManager::nearPlane = -0.1;
float GraphicsManager::farPlane = -40.0;

GLuint GraphicsManager::shaderID = -1;
GLint GraphicsManager::modelUniform = -1;
GLint GraphicsManager::viewUniform = -1;
GLint GraphicsManager::projectionUniform = -1;
GLint GraphicsManager::viewVecUniform = -1;
GLint GraphicsManager::bboxMinUniform = -1;
GLint GraphicsManager::bboxMaxUniform = -1;
GLint GraphicsManager::colorTextureUniform = -1;
GLint GraphicsManager::timeUniform = -1;

void GraphicsManager::init() {
  shaderID = LoadShadersFromFiles();
  modelUniform = glGetUniformLocation(shaderID, "model");
  viewUniform = glGetUniformLocation(shaderID, "view");
  projectionUniform = glGetUniformLocation(shaderID, "projection");
  viewVecUniform = glGetUniformLocation(shaderID, "viewVec");
  bboxMinUniform = glGetUniformLocation(shaderID, "bboxMin");
  bboxMaxUniform = glGetUniformLocation(shaderID, "bboxMax");
  colorTextureUniform = glGetUniformLocation(shaderID, "colorTexture");
  timeUniform = glGetUniformLocation(shaderID, "time");
}

void GraphicsManager::setScreenRatio(float r) {
  screenRatio = r;
  perspectiveProjection = Matrix_Perspective(fov, r, nearPlane, farPlane);
}

void GraphicsManager::setTime(float t) {
  glUniform1f(timeUniform, t);
}

void GraphicsManager::DrawElements(glm::mat4 model, Camera* cam, glm::vec3 bboxMin, glm::vec3 bboxMax, GLuint texture, GLuint vertexArrayID, GLenum drawMode, GLsizei elCount, GLenum type, void* firstIndex) {
  glUseProgram(shaderID);

  glBindVertexArray(vertexArrayID);

  glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewUniform       , 1 , GL_FALSE , glm::value_ptr(cam->getMatrix()));
  glUniformMatrix4fv(projectionUniform , 1 , GL_FALSE , glm::value_ptr(perspectiveProjection));
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

static GLuint LoadShadersFromFiles()
{
    GLuint vertex_shader_id = LoadShader_Vertex("../../src/shader_vertex.glsl");
    GLuint fragment_shader_id = LoadShader_Fragment("../../src/shader_fragment.glsl");

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
