#include "GlobalRenderer.hpp"

float     GlobalRenderer::_uKd             = .98f;
float     GlobalRenderer::_uKs             = 2.96f;
float     GlobalRenderer::_uLightIntensity = 1.12f;
float     GlobalRenderer::_uShininess      = 38.f;
glm::vec3 GlobalRenderer::_lightDir{12.f, 16.f, 14.f};

GlobalRenderer::GlobalRenderer(p6::Context* ctx, TrackballCamera* camera)
    : _ctx(ctx), _camera(camera)
{
    _ctx->maximize_window();
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
};

void GlobalRenderer::drawObject(const glm::mat4& modelMatrix, const Object3D& object) const
{
    glm::vec3 lightPos{0.f, 0.f, 0.f};

    _lightDir = glm::vec4(_lightDir, 1.f) * glm::rotate(glm::mat4(1.f), 0.f, {0.f, 1.f, 0.f});

    glm::mat4 viewMatrix = _camera->getViewMatrix();
    glm::mat4 projMatrix =
        glm::perspective(glm::radians(70.f), _ctx->aspect_ratio(), 0.1f, 1000.f);

    glBindVertexArray(object.getVAO());
    object.getShader().shader.use();

    glUniform3f(object.getShader().uKd, _uKd, _uKd, _uKd);
    glUniform3f(object.getShader().uKs, _uKs, _uKs, _uKs);
    glUniform3fv(object.getShader().uLightDir_vs, 1, glm::value_ptr(glm::vec4(_lightDir, 1.f) * glm::inverse(viewMatrix)));
    glUniform3fv(object.getShader().uLightPos_vs, 1, glm::value_ptr(viewMatrix * glm::vec4(lightPos, 1.f)));
    glUniform3f(object.getShader().uLightIntensity, _uLightIntensity, _uLightIntensity, _uLightIntensity);
    glUniform1f(object.getShader().uShininess, _uShininess);
    glUniform1i(object.getShader().uTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object.getTexture().getTextureID());

    glUniformMatrix4fv(
        object.getShader().uNormalMatrix, 1, GL_FALSE,
        glm::value_ptr(glm::transpose(glm::inverse(viewMatrix * modelMatrix)))
    );
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

void GlobalRenderer::initializeUIElements()
{
    ImGui::Begin("Light parameters");
    ImGui::SliderFloat("Diffuse Reflection", &_uKd, 0.f, 10.f);
    ImGui::SliderFloat("Glossy Reflection", &_uKs, 0.f, 10.f);
    ImGui::SliderFloat("Light Intensity", &_uLightIntensity, 0.f, 2.f);
    ImGui::SliderFloat("Shininess", &_uShininess, 0.f, 100.f);
    ImGui::SliderFloat("Light Direction X", &_lightDir.x, -30.f, 30.f);
    ImGui::SliderFloat("Light Direction Y", &_lightDir.y, -1.f, 30.f);
    ImGui::SliderFloat("Light Direction Z", &_lightDir.z, -30.f, 30.f);
    ImGui::End();
};