#pragma once
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Renderer {
	public:
		void initRenderer();
		void Render(Model model);
	private:
		Shader* shader;
		Camera camera;
		
};
