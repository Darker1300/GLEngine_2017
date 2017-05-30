#pragma once

#include <vector>
#include <algorithm>

class Component;

template<typename T>
class ComponentManager
{
public:
	ComponentManager()
		: m_collection()
	{
		(void)static_cast<Component*>((T*)0);
	}

	void Add(T* _component) {
		m_collection.push_back(_component);
	}

	void Remove(T* _component) {
		auto iter = std::remove(m_collection.begin(), m_collection.end(), _component);
		if (iter != m_collection.end()) m_collection.erase(iter);
	}

	void Clear() { m_collection.clear(); }

	std::vector <T*> m_collection;
};
