#pragma once
#include "Behavior.h"
#include "Application.h"
class PhysicsEngine : public Behavior {
	void init() override;
	void update(ComponentManager* manager) override;
	void exit() override;
	
private:
	void getPhysicsBodies(ComponentManager* manager);
	void updateBodies(ComponentManager* manager);
	void detectCollisions();
	void resolveCollisions();
	void collisionEvents();
	struct PhysicsObject {
		std::shared_ptr<RigidBodyComponent> rb;
		std::shared_ptr<TransformComponent> t;
	};
	std::vector<PhysicsObject> objects;

};