#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"
using bitset = int;
using entity = int;
class ComponentManager {
public:
	template<typename T>
	void addComponent(entity entity, T component);

	template<typename... T>
	void registerComponent();

	template<typename T>
	void removeComponent(entity entity);
	
	template<typename T>
	T* getComponent(entity entity);

	template<typename...T>
	std::tuple<T...> getComponents(entity entity);

	//template <typename T>
	//std::vector<T> getComponents(const std::string* name);

	template<typename T>
	bool hasComponent(entity entity);
private:
	int componentIndex = 1;
	std::unordered_map<entity,bitset> entityComponents;

	std::vector<std::unordered_map<int,Component>> components;
	//TODO: implement sparse set, make vector of sparse sets to store components, use entities as keys for the sparseset
	//TODO: find a way for the user to input a component into functions : either giving access to scene or using comp name or some other method (most likely using the comp name provided by player)
	//std::unordered_map<int, std::vector<componentIndexPair>> entityComponents;
	std::unordered_map<std::string, int> componentID;


};