#pragma once
#include "Mesh.h"
#include "Transform.h"
struct Model { 
	std::vector<Transform> t;
	Mesh* m;
};