#include "GlobalRenderer.hpp"
#include <cmath>

// Global directional illumination parameters

// Cell shading light
// float     GlobalRenderer::_uKd             = 0.1f;          // [GUI]
// float     GlobalRenderer::_uKs             = 1.14f;         // [GUI]
// float     GlobalRenderer::_uLightIntensity = .012f;         // [GUI]
// float     GlobalRenderer::_uShininess      = .006f;         // [GUI]

// Classic light
float     GlobalRenderer::_uKd             = 2.6f;        // [GUI]
float     GlobalRenderer::_uKs             = 3.1f;        // [GUI]
float     GlobalRenderer::_uLightIntensity = 1.3f;        // [GUI]
float     GlobalRenderer::_uShininess      = 57.f;        // [GUI]
glm::vec3 GlobalRenderer::_lightDir{-12.5f, -10.f, -6.f}; // [GUI]

float GlobalRenderer::_time = Math::randExponential(1. / 10.);
float GlobalRenderer::_deltatime;

// Meteo
int                GlobalRenderer::_state = 1;
std::vector<float> GlobalRenderer::_meteo = {0.8, 0.5, 0.2};

GlobalRenderer::GlobalRenderer(p6::Context* ctx, TrackballCamera* camera)
    : _ctx(ctx), _camera(camera)
{
    _ctx->maximize_window();
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    // Initialize point lights
    pointLights[0] = {glm::vec3(2.f, 1.5f, -2.f), glm::vec3(1.0f, 0.f, 0.f), 1.0f, 0.09f, 0.032f, true};
    pointLights[1] = {glm::vec3(-2.f, 1.5f, 2.f), glm::vec3(0.f, 1.0f, 0.2f), 1.0f, 0.09f, 0.032f, false};
};

void GlobalRenderer::drawObject(const glm::mat4& modelMatrix, const Object3D& object, float transparency) const
{
    glm::vec3 lightPos{0.f, 0.f, 0.f};

    _lightDir = glm::vec4(_lightDir, 1.f) * glm::rotate(glm::mat4(1.f), 0.f, {0.f, 1.f, 0.f});

    glm::mat4 viewMatrix = _camera->getViewMatrix();
    glm::mat4 projMatrix =
        glm::perspective(glm::radians(70.f), _ctx->aspect_ratio(), 0.1f, 1000.f);

    glBindVertexArray(object.getVAO());
    object.getShader().shader.use();

    // Handle transparancy
    glDisable(GL_BLEND);
    if (transparency < 1.f)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    // Directional light uniforms
    glUniform3f(object.getShader().uKd, _uKd, _uKd, _uKd);
    glUniform3f(object.getShader().uKs, _uKs, _uKs, _uKs);
    glUniform3fv(object.getShader().uLightDir_vs, 1, glm::value_ptr(glm::vec4(_lightDir, 1.f) * glm::inverse(viewMatrix)));
    glUniform3fv(object.getShader().uLightPos_vs, 1, glm::value_ptr(viewMatrix * glm::vec4(lightPos, 1.f)));

    if (static_cast<int>(fmod(_ctx->time(), _time)) == 0 && (static_cast<int>(fmod(_ctx->time() - _ctx->delta_time(), _time)) != 0))
    {
        _time            = Math::randExponential(1. / 10.);
        _uLightIntensity = _meteo[Math::markovChain(_state)];
    }
    glUniform3f(object.getShader().uLightIntensity, _uLightIntensity, _uLightIntensity, _uLightIntensity);
    glUniform1f(object.getShader().uShininess, _uShininess);

    // Point lights uniforms
    for (size_t i = 0; i < pointLights.size(); i++)
    {
        std::string base = "pointLights[" + std::to_string(i) + "]";
        glUniform3fv(glGetUniformLocation(object.getShader().ID, (base + ".position").c_str()), 1, glm::value_ptr(glm::vec4(pointLights[i].position, 1.f) * glm::inverse(viewMatrix)));
        glUniform3fv(glGetUniformLocation(object.getShader().ID, (base + ".color").c_str()), 1, glm::value_ptr(pointLights[i].color));
        glUniform1f(glGetUniformLocation(object.getShader().ID, (base + ".constant").c_str()), pointLights[i].constant);
        glUniform1f(glGetUniformLocation(object.getShader().ID, (base + ".linear").c_str()), pointLights[i].linear);
        glUniform1f(glGetUniformLocation(object.getShader().ID, (base + ".quadratic").c_str()), pointLights[i].quadratic);
    }

    glUniform1f(object.getShader().uTransparency, transparency);

    glUniform1i(object.getShader().uTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object.getTexture().getTextureID());

    glUniformMatrix4fv(object.getShader().uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(viewMatrix * modelMatrix))));
    glUniformMatrix4fv(object.getShader().uVMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(object.getShader().uMMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(object.getShader().uMVMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix * modelMatrix));
    glUniformMatrix4fv(object.getShader().uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projMatrix * viewMatrix * modelMatrix));

    glDrawArrays(GL_TRIANGLES, 0, object.getMesh().size());
};

void GlobalRenderer::clearAll()
{
    glBindVertexArray(0);            // Ensure no VAO is bound
    glActiveTexture(GL_TEXTURE0);    // Active the default texture unit
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind any 2D textures from the default unit
    _ctx->background({});
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
}

void GlobalRenderer::initializeGUI()
{
    if (ImGui::CollapsingHeader("Light"))
    {
        ImGui::Indent();
        if (ImGui::CollapsingHeader("Global"))
        {
            ImGui::Indent();
            GUIhelp("Adjust how the light reacts on objects.");
            ImGui::SliderFloat("Diffuse Reflection", &_uKd, 0.f, 10.f);
            ImGui::SliderFloat("Glossy Reflection", &_uKs, 0.f, 10.f);
            ImGui::SliderFloat("Shininess", &_uShininess, 0.f, 80.f);
            ImGui::Unindent();
        }
        if (ImGui::CollapsingHeader("Directional light"))
        {
            ImGui::Indent();
            ImGui::SliderFloat("X", &_lightDir.x, -60.f, 60.f);
            ImGui::SliderFloat("Y", &_lightDir.y, -10.f, 60.f);
            ImGui::SliderFloat("Z", &_lightDir.z, -60.f, 60.f);
            ImGui::Unindent();
        }
        ImGui::Unindent();
    }
};