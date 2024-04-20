#pragma once
#include <filesystem>
#include <type_traits>
#include <utility>
#include "Shapes/common.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"
/* ---------- VBO ---------- */
class VBO {
public:
    VBO() { glGenBuffers(1, &_id); }

    ~VBO() { glDeleteBuffers(1, &_id); }

    VBO(const VBO&)            = delete;
    VBO& operator=(const VBO&) = delete;
    VBO(VBO&& other) noexcept // Move constructor
        : _id{other._id}
    {
        other._id = 0; // Make sure that other won't delete the _id we just copied
    }
    VBO& operator=(VBO&& other) noexcept // Move assignment operator
    {
        if (this != &other)
        {                             // Make sure that we don't do silly things when we try to move an object to itself
            glDeleteBuffers(1, &_id); // Delete the previous object
            _id       = other._id;    // Copy the object
            other._id = 0;            // Make sure that other won't delete the _id we just copied
        }
        return *this; // move assignment must return a reference to this, so we do it
    }

    void bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void debind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void bufferData(std::vector<glimac::ShapeVertex> vertices)
    {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);
    }

private:
    GLuint _id{};
};

/* ---------- IBO ---------- */
class IBO {
public:
    IBO() { glGenBuffers(1, &_id); }

    ~IBO() { glDeleteBuffers(1, &_id); }

    IBO(const IBO&)            = delete;
    IBO& operator=(const IBO&) = delete;
    IBO(IBO&& other) noexcept // Move constructor
        : _id{other._id}
    {
        other._id = 0; // Make sure that other won't delete the _id we just copied
    }
    IBO& operator=(IBO&& other) noexcept // Move assignment operator
    {
        if (this != &other)
        {
            glDeleteBuffers(1, &_id); // Delete the previous object
            _id       = other._id;    // Copy the object
            other._id = 0;            // Make sure that other won't delete the _id we just copied
        }
        return *this; // move assignment must return a reference to this, so we do it
    }

    void bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }
    void bufferData(std::vector<glimac::ShapeVertex> vertices)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices.size() * sizeof(uint32_t), vertices.data(), GL_STATIC_DRAW);
    }

    void debind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

private:
    GLuint _id{};
};

/* ---------- VAO ---------- */

class VAO {
public:
    VAO() { glGenVertexArrays(1, &_id); }

    ~VAO() { glDeleteVertexArrays(1, &_id); }

    VAO(const VAO&)            = delete;
    VAO& operator=(const VAO&) = delete;
    VAO(VAO&& other) noexcept
        : _id{other._id} { other._id = 0; } // Move constructor
    VAO& operator=(VAO&& other) noexcept    // Move assignment operator
    {
        if (this != &other)
        {                             // Make sure that we don't do silly things when we try to move an object to itself
            glDeleteBuffers(1, &_id); // Delete the previous object
            _id       = other._id;    // Copy the object
            other._id = 0;            // Make sure that other won't delete the _id we just copied
        }
        return *this; // move assignment must return a reference to this, so we do it
    }

    void bind() const { glBindVertexArray(_id); } // pas besoin de préciser GL_ARRAY... car il y a un unique vao

    void debind() const { glBindVertexArray(0); }

private:
    GLuint _id{};
};

/* ---------- TEXTURE ----------*/

// class Texture {
//     img::Image   image;
//     GLuint       _id{};
//     unsigned int _width;
//     unsigned int _height;

// public:
//     explicit Texture(const std::filesystem::path& path)
//         : image(p6::load_image_buffer(path)), _width(image.width()), _height(image.height())
//     {
//         glGenTextures(1, &_id);
//         bind();
//         parameter();
//         debind();
//     }

//     ~Texture()
//     {
//         glDeleteTextures(1, &_id);
//     }

//     void bind() const { glBindTexture(GL_TEXTURE_2D, _id); }

//     void debind() const { glBindTexture(GL_TEXTURE_2D, 0); }

//     unsigned int   height() const { return _height; }
//     unsigned int   width() const { return _width; } //
//     const uint8_t* data() const { return image.data(); }
//     void           parameter() const
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width(), height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data());
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     }

//     GLuint getId() const { return _id; }
//     void   activeTexture(int i = 0) const
//     {
//         glActiveTexture(GL_TEXTURE0 + i);
//         glBindTexture(GL_TEXTURE_2D, _id);
//     }

//     void deactiveTexture(int i = 0) const
//     {
//         glActiveTexture(GL_TEXTURE0 + i);
//         glBindTexture(GL_TEXTURE_2D, 0);
//     }
// };

struct Vertex2DColor {
    glm::vec2 position;
    glm::vec3 color;
    Vertex2DColor(glm::vec2 vp, glm::vec3 vc)
        : position(vp), color(vc) {}
};

struct Vertex2DUV {
    glm::vec2 position;
    glm::vec2 texture;
    Vertex2DUV();
    Vertex2DUV(glm::vec2 vp, glm::vec2 vc)
        : position(vp), texture(vc) {}
};
