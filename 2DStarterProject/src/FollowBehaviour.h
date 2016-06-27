#pragma once

#include <MathLib.h>
#include <AILib.h>

class FollowBehaviour : public AI::IBehaviour
{
	AI::Agent* m_pCurrentTarget;

public:
	FollowBehaviour(AI::Agent* pTarget);
	virtual ~FollowBehaviour();

	inline AI::Agent* GetTarget() { return m_pCurrentTarget; }
	inline void SetTarget(AI::Agent* pNewTarget) { m_pCurrentTarget = pNewTarget; }

	virtual void Update(AI::Agent* pAgent, float deltaTime);
};