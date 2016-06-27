#pragma once

#include <MathLib.h>

namespace AI
{
	class Agent;
	class IBehaviour
	{
	public:
		IBehaviour() {};
		virtual ~IBehaviour() = 0 {};
		virtual void Update(Agent* pAgent, float deltaTime) = 0;
	};
}