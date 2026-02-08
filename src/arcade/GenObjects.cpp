#include "GenObjects.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh *GenObjects::CreateLine(const std::string &name, const float length,
                           const glm::vec3 start, const bool orientation,
                           const glm::vec3 color) {

    std::vector<VertexFormat> line_vertices;
    line_vertices.push_back(VertexFormat(start, color));

    // orientation TRUE => horizontal; orientation FALSE => vertical
    if (orientation)
        line_vertices.push_back(VertexFormat(start + glm::vec3(length, 0, 0), color));
    else
        line_vertices.push_back(VertexFormat(start + glm::vec3(0, length, 0), color));

    std::vector<unsigned int> line_indices = { 0, 1 };

    Mesh* line = new Mesh(name);
    line->InitFromData(line_vertices, line_indices);

    line->SetDrawMode(GL_LINES);

    return line;
}

Mesh* GenObjects::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2};

    Mesh* square = new Mesh(name);

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* GenObjects::CreateTriangle(const std::string &name, glm::vec3 vert0,
                               glm::vec3 vert1, glm::vec3 vert2,
                               glm::vec3 color, bool fill) {
    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(vert0, color));
    vertices.push_back(VertexFormat(vert1, color));
    vertices.push_back(VertexFormat(vert2, color));

    std::vector<unsigned int> indices = {
        0, 1, 2
    };

    Mesh* triangle = new Mesh(name);

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);

    return triangle;
}

Mesh* GenObjects::CreateCircle(const std::string &name, float radius, glm::vec3 center,
                             glm::vec3 color)
{
    int numSegments = 60;

    std::vector<VertexFormat> vertices;

    vertices.push_back(VertexFormat(center, color));

    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * glm::pi<float>() * (float)i / (float)numSegments;
        glm::vec3 vertex = center + glm::vec3(radius * cos(angle), radius * sin(angle), 0);
        vertices.push_back(VertexFormat(vertex, color));
    }

    std::vector<unsigned int> indices;

    for (int i = 1; i < numSegments; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(numSegments);
    indices.push_back(1);

    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh *GenObjects::CreateSemicircle(const std::string &name, float radius, glm::vec3 center,
                                 glm::vec3 color) {
    int numSegments = 60;

    std::vector<VertexFormat> vertices;

    vertices.push_back(VertexFormat(center, color));

    for (int i = 0; i <= numSegments; i++) {
        float angle = glm::pi<float>() * (float)i / (float)numSegments;
        glm::vec3 vertex = center + glm::vec3(radius * cos(angle), radius * sin(angle), 0);
        vertices.push_back(VertexFormat(vertex, color));
    }

    std::vector<unsigned int> indices;

    for (int i = 1; i <= numSegments; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(numSegments);
    indices.push_back(1);

    Mesh* semicircle = new Mesh(name);
    semicircle->InitFromData(vertices, indices);
    return semicircle;
}

Mesh* GenObjects::CreateTrapeze(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(2 * length, 0, 0), color),
        VertexFormat(corner + glm::vec3(1.5 * length, length, 0), color),
        VertexFormat(corner + glm::vec3(0.5 * length, length, 0), color)
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    Mesh* trapeze = new Mesh(name);

    if (!fill) {
        trapeze->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    trapeze->InitFromData(vertices, indices);
    return trapeze;
}