#include "FollowBehaviour.h"


FollowBehaviour::FollowBehaviour(AI::Agent* pTarget)
{
	m_pCurrentTarget = pTarget;
}

FollowBehaviour::~FollowBehaviour()
{

}

void FollowBehaviour::Update(AI::Agent* pAgent, float deltaTime)
{
	const float SPEED = 3000.0f;
	const float STOPDIST = 100.0f;
	Math::Vector2 target = m_pCurrentTarget->GetPosition();

	Math::Vector2 direction = target - pAgent->GetPosition();
	float distance = direction.Magnitude();
	direction.Normalise();

	// If distance is close, stop
	if (distance < STOPDIST)
		pAgent->SetAcceleration({});
	else
		pAgent->SetAcceleration(direction * SPEED);
}