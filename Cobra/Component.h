#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Mesh.h"

struct Component{

};
struct MeshComponent:public Component {
	Mesh* m;
};


struct TransformComponent :public Component {
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
};


struct CameraComponent :public Component {
	glm::vec3 position;
	glm::vec3 camFront;
	glm::vec3 camUp;
	glm::vec3 camRight;
	glm::mat4 projection;
	float fov;
};
