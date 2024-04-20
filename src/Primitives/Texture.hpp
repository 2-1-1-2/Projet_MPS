#pragma once
#include "p6/p6.h"
#include "stb_image/stb_image.h"

class Texture {
private:
    GLuint      _textureID;    // OpenGL texture ID
    std::string _filePath;     // Path to the texture file
    void        loadTexture(); // Method to load texture from the file

public:
    // Constructor initializes texture with the name of the image file, default to the cube
    explicit Texture(const std::string& name);

    // Returns the OpenGL texture ID
    GLuint getTextureID() const { return _textureID; }
};