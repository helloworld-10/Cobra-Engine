#include "PhysicsEngine.h"


void PhysicsEngine::init()
{
}

void PhysicsEngine::update(ComponentManager* manager)
{
	//(std::static_pointer_cast<SATColliderComponent>(colliders[1].c))->verts->size()
	getPhysicsBodies(manager);
	updateBodies(manager);
	
	getColliderComponents(manager);
	
	detectCollisions(manager);
	
}

void PhysicsEngine::exit()
{
}

void PhysicsEngine::getPhysicsBodies(ComponentManager* manager) {
	objects.clear();
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
		p.rb->velocity += p.rb->force/p.rb->mass * dt;
		p.t->position += p.rb->velocity * dt;
		
		glm::mat4 r = p.t->rotation;
		float e = glm::dot(r[0], r[1]);
		glm::vec3 ox = glm::normalize(r[0] - (e / 2) * r[1]);
		glm::vec3 oy = glm::normalize(r[1] - (e / 2) * r[0]);
		glm::vec3 oz = glm::normalize(glm::cross(ox, oy));
		p.t->rotation = glm::mat3(ox, oy, oz);

		p.rb->L += p.rb->torque*dt;
		glm::vec3 rotVel = p.t->rotation *p.rb->Iinv *glm::transpose(p.t->rotation)*p.rb->L;
		p.t->rotation += glm::mat3(glm::cross(rotVel, p.t->rotation[0]), glm::cross(rotVel, p.t->rotation[1]), glm::cross(rotVel, p.t->rotation[2])) * dt;
		
		p.rb->force = { 0,0,0 };
		p.rb->torque = { 0,0,0 };
		
	}
	
}

void PhysicsEngine::getColliderComponents(ComponentManager* manager) {
	colliders.clear();
	std::vector<entity> colliderEntities = manager->getEntities<ColliderComponent>();
	colliders.reserve(colliderEntities.size());
	for (entity e : colliderEntities) {
		CollisionObject sp;
		sp.e = e;
		sp.c = (manager->getComponent<ColliderComponent>(e));
		sp.t = (manager->getComponent<TransformComponent>(e));
		colliders.push_back(sp);
	}
}

void PhysicsEngine::detectCollisions(ComponentManager* manager)
{
	
	for (int i = 0; i < colliders.size(); i++) {
		for (int j = i+1; j < colliders.size(); j++) {
			if (colliders[i].c->type == Sphere && colliders[j].c->type == Sphere) {
				SphereCollisionObject s1;
				SphereCollisionObject s2;
				s1.c = std::static_pointer_cast<SphereColliderComponent>(colliders[i].c);
				s1.t = colliders[i].t;
				s2.c = std::static_pointer_cast<SphereColliderComponent>(colliders[j].c);
				s2.t = colliders[j].t;
				SphereSphere(s1, s2);
			}
			else if (colliders[i].c->type == SAT && colliders[j].c->type == SAT) {
				SATCollisionObject s1;
				SATCollisionObject s2;
				s1.c = std::static_pointer_cast<SATColliderComponent>(colliders[i].c);
				s1.t = colliders[i].t;
				s2.c = std::static_pointer_cast<SATColliderComponent>(colliders[j].c);
				s2.t = colliders[j].t;
				SATSAT(s1, s2);
			}
			else if (colliders[i].c->type == Sphere && colliders[j].c->type == SAT) {
				SphereCollisionObject s1;
				SATCollisionObject s2;
				s1.c = std::static_pointer_cast<SphereColliderComponent>(colliders[i].c);
				s1.t = colliders[i].t;
				s2.c = std::static_pointer_cast<SATColliderComponent>(colliders[j].c);
				s2.t = colliders[j].t;
				SphereSAT(s1, s2);
			}
			else if (colliders[i].c->type == SAT && colliders[j].c->type == Sphere) {
				SATCollisionObject s1;
				SphereCollisionObject s2;
				s2.c = std::static_pointer_cast<SphereColliderComponent>(colliders[i].c);
				s2.t = colliders[i].t;
				s1.c = std::static_pointer_cast<SATColliderComponent>(colliders[i].c);
				s1.t = colliders[i].t;
				SphereSAT(s2, s1);
			}
			
		}
		
	}
}

void PhysicsEngine::SphereSphere(SphereCollisionObject s1, SphereCollisionObject s2) {
	float sum = s1.c->radius + s2.c->radius;
	if (glm::length(s1.t->position - s2.t->position) <= sum) {
		glm::vec3 norm = glm::normalize(s1.t->position - s2.t->position);
		float depth = sum - glm::length(s1.t->position - s2.t->position);
		s1.t->position += norm * depth/2.0f;
		s2.t->position += -norm * depth/2.0f;

	}
	
}

void PhysicsEngine::SphereSAT(SphereCollisionObject s1, SATCollisionObject s2) {
	std::vector<glm::vec3> s2Translated;
	
	s2Translated.reserve(s2.c->verts->size());
	
	std::vector tmp = *(s2.c->verts);
	
	for (glm::vec3 v : tmp) {
		s2Translated.push_back((v));
	}
	
	std::vector<glm::vec3> axes;
	for (size_t i = 0; i < s2Translated.size(); i++) {
		glm::vec3 edge = s2Translated[(i + 1) % s2Translated.size()] - s2Translated[i];
		glm::vec3 normal = glm::normalize(glm::cross(edge, s2Translated[(i + 2) % s2Translated.size()] - s2Translated[i]));
		axes.push_back(normal);
	}
	float minOverlap = std::numeric_limits<float>::infinity();
	glm::vec3 result;
	float minDist = INFINITY;
	for (glm::vec3 v : s2Translated) {
		float d = glm::length(v - s1.t->position);
		if (d < minDist) {
			minDist = d;
			result = v;
		}
	}
	axes.push_back(glm::normalize(result - s1.t->position));
	
	glm::vec3 smallestAxis;
	for (glm::vec3 v : axes) {
		float minA, maxA, minB, maxB, overlapAmount;
		projectOntoAxis(s2Translated, v, minA, maxA);
		projectSphereOntoAxis(s1.t->position, s1.c->radius, v, minB, maxB);

		
		if ((minA >= maxB || minB >= maxA))
		{
		std:: cout << "sadf" << std::endl;
		}
	
		/* overlapAmount = 0;
		if (overlapAmount < minOverlap) {
			minOverlap = overlapAmount;
			smallestAxis = v;
		}*/
	}
	

}
void PhysicsEngine::projectSphereOntoAxis(const glm::vec3& center, float radius, const glm::vec3& axis, float& minB, float& maxB) {
	// Project the sphere's center onto the axis
	//float centerProjection = glm::dot(center, axis);

	//// The sphere's projection is centered around its center and extends by the radius in both directions
	//minB = centerProjection - radius;
	//maxB = centerProjection + radius;
	//float proj = glm::dot(s1.t->position, v);
	//minB = proj - s1.c->radius;
	//maxB = proj + s1.c->radius;
	/*if (minB > maxB) {
		float t = minB;
		minB = maxB;
		maxB = t;
	}*/
	glm::vec3 dr = radius * axis;
	glm::vec3 p1 = center+dr;
	glm::vec3 p2 = center - dr;
	minB = glm::dot(p1, axis);
	maxB = glm::dot(p2, axis);
	if (minB > maxB)
	{
		// swap the min and max values.
		float t = minB;
		minB = maxB;
		maxB = t;
	}
}

void PhysicsEngine::SATSAT(SATCollisionObject s1, SATCollisionObject s2) {
	std::vector<glm::vec3> s1Translated;
	s1Translated.reserve(s1.c->verts->size());
	std::vector<glm::vec3> s2Translated;
	s2Translated.reserve(s2.c->verts->size());
	std::vector<glm::vec3> tmp1 = *(s1.c->verts);
		std::vector<glm::vec3> tmp2 = *(s2.c->verts);
	for (glm::vec3 v : tmp1) {
		s1Translated.push_back((v + s1.t->position) * s1.t->rotation);
	}
	for (glm::vec3 v : tmp2) {
		s2Translated.push_back((v + s2.t->position) * s2.t->rotation);
	}

	std::vector<glm::vec3> axes;
	float minOverlap = std::numeric_limits<float>::infinity();
	glm::vec3 smallestAxis;

	// Get face normals of poly1
	for (size_t i = 0; i < s1Translated.size(); i++) {
		glm::vec3 edge = s1Translated[(i + 1) % s1Translated.size()] - s1Translated[i];
		glm::vec3 normal = glm::normalize(glm::cross(edge, s1Translated[(i + 2) % s1Translated.size()] - s1Translated[i]));
		axes.push_back(normal);
	}

	// Get face normals of poly2
	for (size_t i = 0; i < s2Translated.size(); i++) {
		glm::vec3 edge = s2Translated[(i + 1) % s2Translated.size()] - s2Translated[i];
		glm::vec3 normal = glm::normalize(glm::cross(edge,s2Translated[(i + 2) % s2Translated.size()] - s2Translated[i]));
		axes.push_back(normal);
	}

	// Cross products of edges of poly1 and poly2 to get more separating axes
	for (size_t i = 0; i < s1Translated.size(); i++) {
		glm::vec3 edge1 = s1Translated[(i + 1) % s1Translated.size()] - s1Translated[i];
		for (size_t j = 0; j < s2Translated.size(); j++) {
			glm::vec3 edge2 = s2Translated[(j + 1) % s2Translated.size()] - s2Translated[j];
			glm::vec3 axis = glm::normalize(glm::cross(edge1,edge2));
			if (axis.x != 0 || axis.y != 0 || axis.z != 0) {
				axes.push_back(axis);
			}
		}
	}

	// Test all axes for separation
	for (const glm::vec3& axis : axes) {
		float minA, maxA, minB, maxB, overlapAmount;
		projectOntoAxis(s1Translated, axis, minA, maxA);
		projectOntoAxis(s2Translated, axis, minB, maxB);

		if (overlap(minA, maxA, minB, maxB, overlapAmount)) {
			std::cout << "hlp" << std::endl; // Found a separating axis, no collision
		}

		if (overlapAmount < minOverlap) {
			minOverlap = overlapAmount;
			smallestAxis = axis;
		}
	}
	// The Minimum Translation Vector (MTV) is along the axis with the smallest overlap
	glm::vec3 MTV = smallestAxis * minOverlap;
}
void PhysicsEngine::projectOntoAxis(const std::vector<glm::vec3>& vertices, const glm::vec3& axis, float& minProj, float& maxProj) {
	minProj = std::numeric_limits<float>::infinity();
	maxProj = -std::numeric_limits<float>::infinity();

	for (const auto& vertex : vertices) {
		float projection = glm::dot(vertex,axis);
		if (projection < minProj) {
			minProj = projection;
		}
		if (projection > maxProj) {
			maxProj = projection;
		}
	}
}

bool PhysicsEngine::overlap(float minA, float maxA, float minB, float maxB, float& overlapAmount) {
	overlapAmount = std::min(maxA, maxB) - std::max(minA, minB);
	return overlapAmount < 0;
}
void PhysicsEngine::AABBAABB(AABBCollisionObject a, AABBCollisionObject b) {
	glm::vec3 amin = a.t->position;
	glm::vec3 amax = a.t->position + a.c->dimensions;
	glm::vec3 bmin = b.t->position;
	glm::vec3 bmax = b.t->position + b.c->dimensions;

	if (amax.x>=bmin.x && bmax.x>=amin.x
		&& amax.y >= bmin.y && bmax.y >= amin.y
		&& amax.z >= bmin.z && bmax.z >= amin.z) {
		float overlapX = std::min(amax.x - bmin.x, bmax.x - amin.x);
		float overlapY = std::min(amax.y - bmin.y, bmax.y - amin.y);
		float overlapZ = std::min(amax.z - bmin.z, bmax.z - amin.z);

		if (overlapX < overlapY && overlapX < overlapZ) {
			if (a.c->isStatic && b.c->isStatic) {
				a.t->position += glm::vec3(overlapX * ((amin.x < bmin.x) ? -1.0f : 1.0f), 0.0f, 0.0f) / 2.0f;
				b.t->position -= glm::vec3(overlapX * ((amin.x < bmin.x) ? -1.0f : 1.0f), 0.0f, 0.0f) / 2.0f;
			}
			else if (a.c->isStatic) {
				b.t->position -= glm::vec3(overlapX * ((amin.x < bmin.x) ? -1.0f : 1.0f), 0.0f, 0.0f);
			}
			else {
				a.t->position += glm::vec3(overlapX * ((amin.x < bmin.x) ? -1.0f : 1.0f), 0.0f, 0.0f);
			}
		}
		else if (overlapY < overlapX && overlapY < overlapZ) {
			
			if (a.c->isStatic && b.c->isStatic) {
				a.t->position += glm::vec3(0.0f, overlapY * ((amin.y < bmin.y) ? -1.0f : 1.0f), 0.0f) / 2.0f;
				b.t->position -= glm::vec3(0.0f, overlapY * ((amin.y < bmin.y) ? -1.0f : 1.0f), 0.0f) / 2.0f;
			}
			else if (a.c->isStatic) {
				b.t->position -= glm::vec3(0.0f, overlapY * ((amin.y < bmin.y) ? -1.0f : 1.0f), 0.0f);
			}
			else {
				a.t->position += glm::vec3(0.0f, overlapY * ((amin.y < bmin.y) ? -1.0f : 1.0f), 0.0f) / 2.0f;
			}
			 
		}
		else {
			
			 
			 if (a.c->isStatic && b.c->isStatic) {
				 a.t->position += glm::vec3(0.0f, 0.0f, overlapZ * ((amin.z < bmin.z) ? -1.0f : 1.0f)) / 2.0f;
				 b.t->position -= glm::vec3(0.0f, 0.0f, overlapZ * ((amin.z < bmin.z) ? -1.0f : 1.0f)) / 2.0f;
			 }
			 else if (a.c->isStatic) {
				 b.t->position -= glm::vec3(0.0f, 0.0f, overlapZ * ((amin.z < bmin.z) ? -1.0f : 1.0f));
			 }
			 else {
				 a.t->position += glm::vec3(0.0f, 0.0f, overlapZ * ((amin.z < bmin.z) ? -1.0f : 1.0f)) ;
			 }
		}
	}
}

void PhysicsEngine::resolveCollisions(CollResponse c)
{

}

void PhysicsEngine::collisionEvents()
{
}
