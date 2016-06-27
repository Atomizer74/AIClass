#include "KeyboardBehaviour.h"
#include <GLFW/glfw3.h>

const float SPEED = 5000.0f;

KeyboardBehaviour::KeyboardBehaviour(BaseApplication* app)
{
	m_app = app;
}

KeyboardBehaviour::~KeyboardBehaviour()
{
}

void KeyboardBehaviour::Update(AI::Agent* pAgent, float deltaTime)
{
	Math::Vector2 accel;
	
	if (m_app->isKeyPressed(GLFW_KEY_LEFT))
		accel.X -= SPEED;
	if (m_app->isKeyPressed(GLFW_KEY_RIGHT))
		accel.X += SPEED;
	if (m_app->isKeyPressed(GLFW_KEY_UP))
		accel.Y += SPEED;
	if (m_app->isKeyPressed(GLFW_KEY_DOWN))
		accel.Y -= SPEED;

	pAgent->SetAcceleration(accel);
}