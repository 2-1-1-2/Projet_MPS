#pragma once
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Cameras/TrackballCamera.hpp"
#include "Primitives/Object3D.hpp"
#include "Shapes/Common.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/matrix.hpp"
#include "p6/p6.h"

class GlobalRenderer {
private:
    static float     _uKd;
    static float     _uKs;
    static float     _uLightIntensity;
    static float     _uShininess;
    static glm::vec3 _lightDir;

    std::vector<Object3D> _objects;
    p6::Context*          _ctx;
    TrackballCamera*      _camera;

public:
    explicit GlobalRenderer(p6::Context* ctx, TrackballCamera* camera);

    // void        addObject(Object3D _objects);
    // void        clearAllObjects();
    void        drawObject(const glm::mat4& modelMatrix, const Object3D& object) const;
    static void initializeUIElements();
    void        close();
};