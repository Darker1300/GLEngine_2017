
#pragma once

#include <vector>

class Scene;

class SceneEngine
{
	friend class Core;

public:
	Scene* const At(unsigned int _Index) const;
	Scene* const Active() const;
	int ActiveIndex() const;
	int SceneCount() const;

	void SetActive(const Scene* _scene);
	void SetActive(int _index);
	void SetNext();
	void Add(Scene* _scene);
	void Clear();

protected:
	static void Initialize();
	static void Finalize();

	SceneEngine();
	~SceneEngine();

	std::vector<Scene*> m_scenes;
	int m_currentIndex;
};

