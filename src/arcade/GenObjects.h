#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace GenObjects
{

    Mesh* CreateLine(const std::string &name, float length, glm::vec3 start, bool orientation, glm::vec3 color);
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string &name, glm::vec3 vert0, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string &name, float radius, glm::vec3 center, glm::vec3 color);
    Mesh* CreateSemicircle(const std::string &name, float radius, glm::vec3 center, glm::vec3 color);
    Mesh* CreateTrapeze(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

}