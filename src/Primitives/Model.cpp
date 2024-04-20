#include "Model.hpp"

Model::Model(const std::string& name)
    : _filePath("assets/models/" + name + ".obj") // Construct the full path to the model file
{
    // Attempt to load the model, and print an error if unsuccessful
    if (!loadModel())
    {
        std::cerr << "loadModel() failed: couldn't load model named [" << name << "]." << std::endl;
    }
}

// Attempts to load the model from the file, returns true on success
bool Model::loadModel()
{
    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      err;
    std::string                      warn;

    // Load the object file
    const bool loadSuccess = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _filePath.c_str());
    if (!loadSuccess)
    {
        std::cerr << "LoadObj() failed: " << err << std::endl;
        return loadSuccess;
    }

    // Loop over shapes in the model
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

            // Construct a vertex and add to the list of vertices
            _vertices.emplace_back(position, normal, texCoord);
        }
    }

    return loadSuccess;
}