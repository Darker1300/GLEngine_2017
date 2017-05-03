#pragma once

class TimeKeeper
{
	friend class Core;

public:
	float FixedDeltaTime() const;
	float DeltaTime() const;
	///<summary>Time at current Frame.</summary>
	double NowTime() const;
	///<summary>Time at last Frame.</summary>
	double LastTime() const;
	///<summary>Frames Per a Second.</summary>
	float FPS() const;
	unsigned int iFPS() const;

	///<summary>Set Time Scale, modifies Delta Time. Defaults to 1.0.</summary>
	void SetTimeScale(float _timeScale);
	///<summary>Set ideal Fixed Updates Per Second. Defaults to 60.</summary>
	void SetFUPS(unsigned int _fups);

protected:

	static void Initialize();
	static void Finalize();

	TimeKeeper();
	~TimeKeeper();

	void Core_StartFrame();
	bool Core_FixedUpdateTick();

	double m_lastFrameTime;
	double m_currentFrameTime;
	float m_deltaTime;
	float m_timeScale;

	///<summary>Number of Fixed Updates ready to consume.</summary>
	float m_remainingFixedUpdates;
	///<summary>Ideal Fixed Updates Per a Second.</summary>
	unsigned int m_targetFUPS;
	///<summary>Fixed Delta Time for a single frame.</summary>
	float m_FDTInterval;

	///<summary>Used to calculate FPS & CurrentFixedUpdates every second.</summary>
	float m_FPSTimer;

	///<summary>Frames Per a Second.</summary>
	float m_FPS;
};

