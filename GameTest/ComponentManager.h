#pragma once
#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include <vector>
#include <unordered_map>

template<typename Component>
class ComponentManager
{
public:

private:
	// Storing the maps we need for entities
	std::vector<Component> components;
	
};

#endif // !__COMPONENTMANAGER_H__

