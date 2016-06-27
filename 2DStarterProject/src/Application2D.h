#pragma once

#include <AILib.h>
#include <MathLib.h>
#include "BaseApplication.h"

#include <list>

class SpriteBatch;
class Texture;
class Font;

class Application2D : public BaseApplication {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();

protected:
	const float NODESPACING = 50;

	AI::Graph*		m_pGraph;
	AI::Graph::Node* m_pStartNode;
	AI::Graph::Node* m_pEndNode;
	std::list<std::pair<AI::Graph::Node*,AI::Graph::Node*>> m_Path;

	SpriteBatch*	m_spriteBatch;
	Texture*		m_nodeTex;
	Font*			m_font;
};