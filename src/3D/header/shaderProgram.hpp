#pragma once
#include <string>
#include <vector>
#include "glm/ext/vector_float4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
// #include "glfw/src/internal.h"

class ShaderProgram {
protected:
    p6::Shader m_Program;

    GLint              uMVPMatrix;
    GLint              uMVMatrix;
    GLint              uNormalMatrix;
    std::vector<GLint> uTextures;

public:
    ShaderProgram(const std::filesystem::path& vs, const std::filesystem::path& fs)
        : m_Program{p6::load_shader(vs, fs)}, uMVPMatrix(glGetUniformLocation(m_Program.id(), "uMVPMatrix")), uMVMatrix(glGetUniformLocation(m_Program.id(), "uMVMatrix")), uNormalMatrix(glGetUniformLocation(m_Program.id(), "uNormalMatrix"))
    {
        // uTextures.push_back(glGetUniformLocation(m_Program.id(), nomVardansGLSL));

        // std::cout << "dans cette fonction\n";
        // addTextures();
    }

    virtual void addTextures() = 0;

    void addTexture(const std::string tex)
    {
        std::cout << "dans addTextures sans s\n";
        std::cout << tex << "\n";
        uTextures.push_back(glGetUniformLocation(m_Program.id(), tex.c_str()));
    }

    void use()
    {
        m_Program.use();
    }

    void uniformText()
    {
        for (int i = 0; i < uTextures.size(); i++)
        {
            glUniform1i(uTextures.at(i), i);
        }
    }

    void transformation(glm::mat4 ProjMatrix, const glm::mat4 MVMatrix, const glm::mat4 camMatrix)
    {
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    }
};

class EarthProgram : public ShaderProgram {
public:
    EarthProgram(const std::filesystem::path& vs, const std::filesystem::path& fs)
        : ShaderProgram(vs, fs)
    {
        addTextures();
    };
    void addTextures() override
    {
        std::cout << "dans addTextures avec s\n";
        addTexture("uEarthTexture");
        addTexture("uCloudTexture");
    }
};

class MoonProgram : public ShaderProgram {
public:
    MoonProgram(const std::filesystem::path& vs, const std::filesystem::path& fs)
        : ShaderProgram(vs, fs)
    {
        addTextures();
    };
    void addTextures() override
    {
        std::cout << "dans addTextures avec s\n";
        addTexture("uTexture");
    }
};

class LightProgram : public ShaderProgram {
    GLint uKd;
    GLint uKs;
    GLint uShininess;

    /* GLint uLightDir_vs; */
    GLint uLightPos_vs;
    GLint uLightIntensity;

public:
    LightProgram(const std::filesystem::path& vs, const std::filesystem::path& fs)
        : ShaderProgram(vs, fs), uKd(glGetUniformLocation(m_Program.id(), "uKd")), uKs(glGetUniformLocation(m_Program.id(), "uKs")), uShininess(glGetUniformLocation(m_Program.id(), "uShininess")), uLightPos_vs(glGetUniformLocation(m_Program.id(), "uLightPos_vs")), uLightIntensity(glGetUniformLocation(m_Program.id(), "uLightIntensity"))
    {
    }
    void addTextures() override
    {
        std::cout << "dans addTextures avec s\n";
    }

    void transform(glm::mat4 ProjMatrix, const glm::mat4 MVMatrix, const glm::mat4 camMatrix, float time)
    {
        glm::vec3 dir       = {1.f, 1.f, 1.f};
        glm::mat4 rot       = glm::rotate(camMatrix, time, {0.f, 5.f, 0.f});
        glm::mat  scale_rot = glm::scale(rot, glm::vec3{time});
        ;
        glm::vec3 res = dir * glm::mat3(scale_rot);
        // dir * glm::mat3(glm::rotate(MVMatrix, time, dir));
        //   glm::vec3(1.) * time * glm::mat3(MVMatrix);
        transformation(ProjMatrix, MVMatrix, camMatrix);
        glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3{1.}));
        glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3{0.4, 0.2, 0.6}));
        glUniform1f(uShininess, 1.);

        glUniform3fv(uLightPos_vs, 1, glm::value_ptr(res));
        glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(.9)));
    }
};