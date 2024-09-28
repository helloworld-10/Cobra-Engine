#pragma once
#include "Model.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ComponentManager.h"
#include "Component.h"
#include "Behavior.h"
class Renderer : public Behavior{
	public:
		 void init() override;
		 void update(ComponentManager* manager) override;
		 void exit() override;
	private:
		Shader* shader;	
		void findCamera(ComponentManager* manager);
		void Render(std::shared_ptr<MeshComponent> mesh, std::vector<TransformComponent> transforms);
	std::shared_ptr<CameraComponent> camera;
		std::unordered_map<std::shared_ptr<MeshComponent>, std::vector<TransformComponent>> meshes;
		std::vector <PointLightComponent> lights;
		std::vector<TransformComponent> lightTransforms;
		std::shared_ptr<DirectionalLightComponent> sun;
};
