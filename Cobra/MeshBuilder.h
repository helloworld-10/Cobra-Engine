#pragma once
#include <vector>
#include "GLAD/glad.h"
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <string>
#include "glm/vec3.hpp"
#include "Mesh.h"
#include "Component.h"

class MeshBuilder {
public:
	static MeshComponent createMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::string* texname);
	static MeshComponent loadFromObj(const std::string* filename, const std::string* texname);
};

