#ifndef OBJENTITY_H
#define OBJENTITY_H

#include <string>
#include <vector>
#include <glcommon.h>

#include "tiny_obj_loader.h"
#include "Entity.h"
#include "Camera.hpp"


class ObjEntity : public Entity
{
private:
    std::vector<GLuint> vboIDs;
    std::vector<int> firstIndex;
    std::vector<int> indexCount;
    std::vector<glm::vec3> bboxMin;
    std::vector<glm::vec3> bboxMax;
    std::vector<GLuint> textureID;

    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;

    void computeNormals();
    void buildTriangles(std::string basepath);
    GLuint loadTexture(std::string filename);

public:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 rotation = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    ObjEntity(const char* filename);

    void update(float deltaTime);
    void draw(Camera* c);
};

#endif // OBJENTITY_H
