#pragma once

#include "BaseApplication.h"

#include <MathLib.h>
#include <AILib.h>

class KeyboardBehaviour : public AI::IBehaviour
{
	BaseApplication* m_app;

public:
	KeyboardBehaviour(BaseApplication* app);
	virtual ~KeyboardBehaviour();

	virtual void Update(AI::Agent* pAgent, float deltaTime);
};