#pragma once
#include "Object3D.hpp"
#include "Transform.hpp"
#include "p6/p6.h"

class GameObject {
protected: // Changed from private to protected for inheritance access
    Object3D  _object3D;
    Transform _transform;

public:
    GameObject(){};

    Object3D&  getObject3D() { return _object3D; };
    Transform& getTransform() { return _transform; };
};