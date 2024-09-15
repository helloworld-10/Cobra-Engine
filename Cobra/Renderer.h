#pragma once
#include "Model.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ComponentManager.h"
#include "Component.h"
class Renderer {
	public:
		void initRenderer();
		//void Render(Model model);
		void Render(ComponentManager* manager);
	private:
		Shader* shader;	
		void findCamera(ComponentManager* manager);
		void Render(std::shared_ptr<MeshComponent> mesh, std::vector<TransformComponent> transforms);
	std::shared_ptr<CameraComponent> camera;
		std::unordered_map<std::shared_ptr<MeshComponent>, std::vector<TransformComponent>> meshes;
};
