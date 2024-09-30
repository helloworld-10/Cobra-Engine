#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Mesh.h"

struct Component{

};
struct MeshComponent:public Component {
	std::vector<Vertex> verts;
	std::vector<unsigned int> indices;
	Texture texture;
	unsigned int VAO, VBO, EBO;
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
	float fov = 45;
};

struct DirectionalLightComponent :public Component {
	glm::vec3 direction;
	glm::vec3 color;
};

struct PointLightComponent :public Component {
	glm::vec3 color;
	glm::vec3 attenuation;
};

struct SpotlightComponent :public Component {
	glm::vec3  direction;
	glm::vec3 color;
	float innerCutoff;
	float outerCutoff;
};

struct SphereColliderComponent :public Component {
	glm::vec3 offset;
	float radius;
};

struct AABBColliderComponent :public Component {
	glm::vec3 offset;
	float width;
	float height;
	float depth;
};

struct OBBColliderComponent :public Component {
	glm::vec3 offset;
	glm::vec3 axisX;
	glm::vec3 axisY;
	glm::vec3 axisZ;
	glm::vec3 halfSize;


};

struct RigidBodyComponent :public Component {
	glm::vec3 velocity;
	glm::vec3 rotationalVelocity;
	float mass;
	glm::vec3 COM;
	bool movable;
};