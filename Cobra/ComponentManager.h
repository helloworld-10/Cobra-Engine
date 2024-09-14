#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"
#include <bitset>
//struct componentIndexPair {
//	int id;
//	int index;
//};
class ComponentManager {
public:
	void addComponent(int entity, Component* component);
	void registerComponent(Component* component);
	void removeComponent(int entity, const std::string* name);
	Component* getComponent(int entity, const std::string* name);
	std::vector<Component> getComponents(const std::string* name);
private:
	int componentIndex = 0;
	std::unordered_map<std::bitset<100>, std::vector<int>> hasComponent;
	std::vector<std::unordered_map<int,Component>> components;
	//TODO: implement sparse set, make vector of sparse sets to store components, use entities as keys for the sparseset
	//TODO: find a way for the user to input a component into functions : either giving access to scene or using comp name or some other method (most likely using the comp name provided by player)
	//std::unordered_map<int, std::vector<componentIndexPair>> entityComponents;
	std::unordered_map<std::string, int> componentID;


};