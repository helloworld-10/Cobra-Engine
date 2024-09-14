#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Mesh.h"
struct Component {
	std::string name;
};

template<typename SubComponent>
struct ComponentName :Component {
	const std::string name;
};
struct MeshComponent :ComponentName<MeshComponent> {
	Mesh* m;
	const std::string name = "MeshComponent";
};
struct TransformComponent :ComponentName<TransformComponent> {
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	const std::string name = "TransformComponent";
};

struct CameraComponent :ComponentName<CameraComponent> {
	glm::vec3 position;
	glm::vec3 camFront;
	glm::vec3 camUp;
	glm::vec3 camRight;
	float fov;
	const std::string name = "CameraComponent";
};

