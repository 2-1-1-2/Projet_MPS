#pragma once
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "Shapes/Common.hpp"
#include "tiny_obj_loader.h"

std::vector<glimac::ShapeVertex> loadFile(const std::string& filename);