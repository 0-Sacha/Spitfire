#pragma once

namespace Spitfire {

	struct TimeStep
	{
		TimeStep(float timeStep = 0.0f)
			: m_TimeStep(timeStep) { }

		operator float() const { return m_TimeStep; }
		inline float GetSecond() const { return m_TimeStep; }
		inline float GetMillisecond() const { return m_TimeStep * 1000; }
		inline size_t GetFPS() const { return 1.0f / m_TimeStep; }

	private:
		float m_TimeStep;
	};

}