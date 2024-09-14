#include "ComponentManager.h"

void ComponentManager::addComponent(int entity, Component* component)
{
	int id = componentID[component->name];
	components[id][entity]= *component;
}

void ComponentManager::registerComponent(Component* component)
{
	componentID.try_emplace(component->name, componentIndex);
	componentIndex++;
}

void ComponentManager::removeComponent(int entity, const std::string* name)
{
	int id = componentID[*name];
	components[id].erase(entity);
}

Component* ComponentManager::getComponent(int entity, const std::string* name)
{
	int id = componentID[*name];
	if (components[id].find(entity) != components[id].end()) {
		return &components[id][entity];
	}
	else {
		Component* c = NULL;
		return c;
	}
}
std::vector<Component> ComponentManager::getComponents(const std::string* name)
{
	return std::vector<Component>();
}
