#pragma once
#include "IBehaviour.h"

#include <MathLib.h>
#include <list>


namespace AI
{

	class Agent
	{
	public:
		Agent();
		Agent(const Math::Vector2& position);
		virtual ~Agent();

		inline Math::Vector2 GetPosition() { return m_position; }
		inline void AddBehaviour(IBehaviour* behaviour) { m_behaviours.push_back(behaviour); }

		inline void AddForce(const Math::Vector2& refForce) { m_force += refForce; }
		inline void SetAcceleration(const Math::Vector2& refAcceleration) { m_acceleration = refAcceleration; }

		void Update(float deltaTime);

	protected:
		std::list<IBehaviour*> m_behaviours;

		Math::Vector2 m_force;
		Math::Vector2 m_acceleration;
		Math::Vector2 m_velocity;
		Math::Vector2 m_position;
	};

}