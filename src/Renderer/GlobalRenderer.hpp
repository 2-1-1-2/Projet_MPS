#pragma once
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cameras/TrackballCamera.hpp"
#include "GUI/GUIhelper.hpp"
#include "Maths/Math.hpp"
#include "Primitives/Object3D.hpp"
#include "Shapes/Common.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/matrix.hpp"
#include "p6/p6.h"

struct PointLight {
    glm::vec3 position;
    glm::vec3 color;
    float     constant;
    float     linear;
    float     quadratic;
    bool      followPlayer; // Not working right now
};

class GlobalRenderer {
private:
    static float              _uKd;             // [GUI]
    static float              _uKs;             // [GUI]
    static float              _uLightIntensity; // [GUI]
    static float              _uShininess;      // [GUI]
    static glm::vec3          _lightDir;        // [GUI]
    static int                _state;
    static std::vector<float> _meteo;

    std::vector<Object3D> _objects;
    p6::Context*          _ctx;
    TrackballCamera*      _camera;

    std::array<PointLight, 2> pointLights;

public:
    explicit GlobalRenderer(p6::Context* ctx, TrackballCamera* camera);

    void        drawObject(const glm::mat4& modelMatrix, const Object3D& object, float transparency = 1.f) const;
    void        clearAll();
    static void initializeGUI();
};