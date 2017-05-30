#include "SceneEngine.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "EngineDefines.h"

#include "Scene.h"

#include <algorithm>


Scene * const SceneEngine::At(unsigned int _Index) const
{
	return m_scenes[_Index];
}

Scene * const SceneEngine::Active() const
{
	return m_scenes[m_currentIndex];
}

int SceneEngine::ActiveIndex() const
{
	return m_currentIndex;
}

int SceneEngine::SceneCount() const
{
	return m_scenes.size();
}

void SceneEngine::SetActive(const Scene * _scene)
{
	SetActive(_scene->m_buildIndex);
}

void SceneEngine::SetActive(int _index)
{
	if (_index < 0) LOG_ERROR("Cannot be set to negative index.");
	m_currentIndex = _index;
}

void SceneEngine::SetNext()
{
	m_currentIndex++;
	if (m_currentIndex >= (int)m_scenes.size()) m_currentIndex = 0;
}

void SceneEngine::Add(Scene * _scene)
{
	m_scenes.push_back(_scene);
}

void SceneEngine::Clear()
{
	// Cleanup Scenes
	for (auto iter = m_scenes.begin(); iter != m_scenes.end(); iter++)
		delete (*iter);
	m_scenes.clear();
	m_currentIndex = 0;
}

void SceneEngine::Initialize()
{
	if (ENGINE::SCENES() != nullptr) LOG_ERROR("Attempted to Initialize SceneEngine multiple times.");
	ENGINE::_internals::SCENES = new SceneEngine();

	Scene* sc = new Scene();
	sc->m_name = "Main";

	ENGINE::SCENES()->Add(sc);
	ENGINE::SCENES()->m_currentIndex = 0;
}

void SceneEngine::Finalize()
{
	if (ENGINE::SCENES() == nullptr) LOG_ERROR("Failed to Finalize SceneEngine.");

	ENGINE::SCENES()->Clear();

	delete ENGINE::SCENES();
}

SceneEngine::SceneEngine()
	: m_scenes()
	, m_currentIndex()
{
}

SceneEngine::~SceneEngine()
{
}
