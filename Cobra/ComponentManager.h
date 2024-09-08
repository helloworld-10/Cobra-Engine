#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"
class ComponentManager {
public:
	void addComponent(long entity, Component component);
private:
	//std::unordered_map<std::string, long> entities;
	std::unordered_map<long, std::vector<Component*>> entityComponents;


};