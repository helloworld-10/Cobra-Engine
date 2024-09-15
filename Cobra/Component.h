#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Mesh.h"

struct Component{};
struct MeshComponent:Component {
	Mesh* m;
};


struct TransformComponent :Component {
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
};


struct CameraComponent :Component {
	glm::vec3 position;
	glm::vec3 camFront;
	glm::vec3 camUp;
	glm::vec3 camRight;
	float fov;
	
};
