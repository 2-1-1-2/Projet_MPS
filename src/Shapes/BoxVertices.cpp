#include "BoxVertices.hpp"
#include <vector>

namespace glimac {

std::vector<ShapeVertex> box_vertices(float width, float height, float depth)
{
    std::vector<ShapeVertex> vertices{
        // Front face
        {{-width, -height, depth}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        {{width, -height, depth}, {0.f, 0.f, 1.f}, {1.f, 0.f}},
        {{width, height, depth}, {0.f, 0.f, 1.f}, {1.f, 1.f}},
        {{-width, height, depth}, {0.f, 0.f, 1.f}, {0.f, 1.f}},
        // Back face
        {{-width, -height, -depth}, {0.f, 0.f, -1.f}, {1.f, 0.f}},
        {{width, -height, -depth}, {0.f, 0.f, -1.f}, {0.f, 0.f}},
        {{width, height, -depth}, {0.f, 0.f, -1.f}, {0.f, 1.f}},
        {{-width, height, -depth}, {0.f, 0.f, -1.f}, {1.f, 1.f}},
        // Left face
        {{-width, -height, -depth}, {-1.f, 0.f, 0.f}, {0.f, 0.f}},
        {{-width, height, -depth}, {-1.f, 0.f, 0.f}, {1.f, 0.f}},
        {{-width, height, depth}, {-1.f, 0.f, 0.f}, {1.f, 1.f}},
        {{-width, -height, depth}, {-1.f, 0.f, 0.f}, {0.f, 1.f}},
        // Right face
        {{width, -height, -depth}, {1.f, 0.f, 0.f}, {1.f, 0.f}},
        {{width, height, -depth}, {1.f, 0.f, 0.f}, {0.f, 0.f}},
        {{width, height, depth}, {1.f, 0.f, 0.f}, {0.f, 1.f}},
        {{width, -height, depth}, {1.f, 0.f, 0.f}, {1.f, 1.f}},
        // Upper face
        {{-width, height, -depth}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
        {{width, height, -depth}, {0.f, 1.f, 0.f}, {1.f, 0.f}},
        {{width, height, depth}, {0.f, 1.f, 0.f}, {1.f, 1.f}},
        {{-width, height, depth}, {0.f, 1.f, 0.f}, {0.f, 1.f}},
        // Low face
        {{-width, -height, -depth}, {0.f, -1.f, 0.f}, {1.f, 0.f}},
        {{width, -height, -depth}, {0.f, -1.f, 0.f}, {0.f, 0.f}},
        {{width, -height, depth}, {0.f, -1.f, 0.f}, {0.f, 1.f}},
        {{-width, -height, depth}, {0.f, -1.f, 0.f}, {1.f, 1.f}}
    };

    return vertices;
}

} // namespace glimac