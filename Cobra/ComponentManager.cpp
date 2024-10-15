#include "ComponentManager.h"


std::vector<entity> ComponentManager::getEntities() {
	std::vector<entity> out;
	out.reserve(entityComponents.size());
	for (const auto& pair : entityComponents) {
		out.push_back(pair.first);
	}
	return out;
}
//template <typename T>
//std::vector<T> ComponentManager::getComponents(const std::string* name)
//{
//	int id = componentID[*name];
//	std::vector<T> out;
//	out.reserve(components[id].size);
//	for (const auto& pair : components[id]) {
//		out.push_back(pair.first);
//	}
//	return out;
//}
