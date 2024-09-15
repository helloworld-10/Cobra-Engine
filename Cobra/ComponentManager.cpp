#include "ComponentManager.h"
template<typename T>
void ComponentManager::addComponent(entity entity, T component)
{
	
	if (!ComponentManager::hasComponent<T>(entity)) {
		int id = componentID[component.name];
		components[id][entity] = component;
		entityComponents[entity] += id;
	}
	else {
		return;
	}
}

template<typename... T>
void ComponentManager::registerComponent()
{
	for (const auto p : { T... }) {
		componentID.try_emplace(p.name, componentIndex);
		componentIndex *= 2;
	}

}

template<typename T>
void ComponentManager::removeComponent(entity entity)
{
	if (ComponentManager::hasComponent<T>(entity)) {
		int id = componentID[typeid(T).name];
		components[id].erase(entity);
		entityComponents[entity] -= id;
	}
}

template<typename T>
bool ComponentManager::hasComponent(entity entity)
{
	int id = componentID[typeid(T).name];
	bitset bits = entityComponents[entity];
	return ((bits & id) > 0) ?  true :  false;
}

template<typename T>
T* ComponentManager::getComponent(entity entity)
{
	int id = componentID[typeid(T).name];
	if (components[id].find(entity) != components[id].end()) {
		return   static_cast<T*>(&components[id][entity]);
	}
	else {
		T* c = nullptr;
		return c;
	}
}

template<typename ...T>
std::tuple<T...> ComponentManager::getComponents(entity entity)
{
	return std::make_tuple(getComponent<T>(entity)...);
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
