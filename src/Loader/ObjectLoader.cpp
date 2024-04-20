#include "ObjectLoader.hpp"

std::vector<glimac::ShapeVertex> loadFile(const std::string& filename)
{
    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      err;
    std::string                      warn;

    std::string filepath = "assets/models/" + filename;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str()))
    {
        std::cerr << "LoadObj() failed: " << err << std::endl;
        return {};
    }

    std::vector<glimac::ShapeVertex> vertices;

    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            glm::vec3 position(
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            );

            glm::vec3 normal(
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            );

            glm::vec2 texCoord(
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
            );

            vertices.push_back(glimac::ShapeVertex{position, normal, texCoord});
        }
    }

    return vertices;
}