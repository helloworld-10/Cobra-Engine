#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Mesh.h"
struct Component {
};

template<typename SubComponent>
struct ComponentStatic :Component {
	friend class ComponentManager;
	private:
		static int id;
		static int mask;
};
struct MeshComponent :ComponentStatic<MeshComponent> {
	Mesh* m;
};
struct TransformComponent :ComponentStatic<TransformComponent> {
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
};

struct CameraComponent :ComponentStatic<CameraComponent> {
	glm::vec3 position;
	glm::vec3 camFront;
	glm::vec3 camUp;
	glm::vec3 camRight;
	float fov;
};

