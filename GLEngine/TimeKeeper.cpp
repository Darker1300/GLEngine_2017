#include "TimeKeeper.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "CoreDefines.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>


void TimeKeeper::Initialize()
{
	if (ENGINE::TIME != nullptr) LOG_ERROR("Attempted to Initialize TimeKeeper multiple times.");

	ENGINE::TIME = new TimeKeeper();
}

void TimeKeeper::Finalize()
{
	if (ENGINE::TIME == nullptr) LOG_ERROR("Failed to Finalize TimeKeeper.");

	delete ENGINE::TIME;
}

float TimeKeeper::FixedDeltaTime() const
{
	return m_FDTInterval;
}

float TimeKeeper::DeltaTime() const
{
	return m_deltaTime;
}

double TimeKeeper::NowTime() const
{
	return m_currentFrameTime;
}

double TimeKeeper::LastTime() const
{
	return m_lastFrameTime;
}

float TimeKeeper::FPS() const
{
	return m_FPS;
}

unsigned int TimeKeeper::iFPS() const
{
	return (unsigned int)ceilf(m_FPS);
}

void TimeKeeper::SetTimeScale(float _timeScale)
{
	m_timeScale = _timeScale;
}

void TimeKeeper::SetFUPS(unsigned int _fups)
{
	m_targetFUPS = _fups;
	m_FDTInterval = 1.0f / m_targetFUPS;
}

TimeKeeper::TimeKeeper()
	: m_currentFrameTime(glfwGetTime())
	, m_lastFrameTime(m_currentFrameTime)
	, m_deltaTime()
	, m_timeScale(1.0f)
	, m_remainingFixedUpdates()
	, m_targetFUPS()
	, m_FDTInterval()
	, m_FPSTimer()
	, m_FPS()
{
	SetFUPS(60);
}

TimeKeeper::~TimeKeeper()
{
}

void TimeKeeper::Core_StartFrame()
{
	m_lastFrameTime = m_currentFrameTime;
	m_currentFrameTime = glfwGetTime();

	m_deltaTime = (float)(m_currentFrameTime - m_lastFrameTime);
	// Calculate how many Fixed Updates are remaining
	m_remainingFixedUpdates += m_deltaTime / m_FDTInterval;


	m_FPS = 1.0f / m_deltaTime;

	m_deltaTime *= m_timeScale;
}

bool TimeKeeper::Core_FixedUpdateTick()
{
	if (m_remainingFixedUpdates >= 1.0f) {
		m_remainingFixedUpdates -= 1.0f;
		return true;
	}
	return false;
}
