#pragma once
#include <vector>
#include <string>
#include "Vertex.h"
#include "Texture.h"


struct Mesh{
	std::vector<Vertex> verts;
	std::vector<unsigned int> indices;
	Texture texture;
	unsigned int VAO, VBO, EBO;
};