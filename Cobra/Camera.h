#pragma once
#include "glm/vec3.hpp"
struct Camera {
	glm::vec3 position;
	glm::vec3 camFront;
	glm::vec3 camUp;
	glm::vec3 camRight;
	glm::mat4 projection;
};