#include "PhysicsEngine.h"


void PhysicsEngine::init()
{
}

void PhysicsEngine::update(ComponentManager* manager)
{
	getPhysicsBodies(manager);
	updateBodies(manager);
	
}

void PhysicsEngine::exit()
{
}

void PhysicsEngine::getPhysicsBodies(ComponentManager* manager) {
	std::vector<entity> physicsEntities = manager->getEntities<RigidBodyComponent>();
	objects.reserve(physicsEntities.size());
	for (entity e : physicsEntities) {
		PhysicsObject p;
		p.rb = (manager->getComponent<RigidBodyComponent>(e));
		p.t = (manager->getComponent<TransformComponent>(e));
		objects.push_back(p);
	}
}

void PhysicsEngine::updateBodies(ComponentManager* manager)
{
	float dt = Application::getDeltaTime();
	for (PhysicsObject p : objects) {
		dt = Application::getDeltaTime();
		p.rb->velocity += p.rb->accel * dt;

		p.t->position += p.rb->velocity * dt;


		p.t->rotation += p.rb->rotationalVelocity * dt;
		p.rb->accel = { 0,0,0 };


	}
	objects.clear();
}

void PhysicsEngine::detectCollisions()
{
}

void PhysicsEngine::resolveCollisions()
{
}

void PhysicsEngine::collisionEvents()
{
}
