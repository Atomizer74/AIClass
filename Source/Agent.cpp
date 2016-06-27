#include "Agent.h"

namespace AI
{
	Agent::Agent()
	{

	}

	Agent::Agent(const Math::Vector2& position)
	{
		m_position = position;
	}

	Agent::~Agent()
	{
		for each (IBehaviour* behaviour in m_behaviours)
		{
			delete behaviour;
		}
		m_behaviours.clear();
	}

	void Agent::Update(float deltaTime)
	{
		// TODO: Sensing Calculations
		// TODO: Thinking Calculations
		//		 Add or remove behaviours from the list

		// Acting:
		for each (IBehaviour* beh in m_behaviours)
		{
			beh->Update(this, deltaTime);
		}

		// TODO: Physics stuff with force, acceleration, velocity etc...

		// Force - For now, just add force to velocity and then zero force
		// Done it this way as a force represents an "instant" pulse of acceleration
		m_velocity += m_force;
		m_force = Math::Vector2 {};

		// Acceleration - Just add acceleration taking into account deltaTime
		// acceleration is change in velocity over time, this is why we dont modify acceleration here
		m_velocity += m_acceleration * deltaTime;

		// Apply friction, for now just a magic constant
		// This will slow down the velocity over time
		m_velocity *= 0.8f;

		// Apply the velocity to the position
		// Velocity is the actual change in position over time, so, just add the velocity based on deltaTime
		m_position += m_velocity * deltaTime;
	}
}