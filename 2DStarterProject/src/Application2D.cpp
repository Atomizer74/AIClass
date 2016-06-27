#include "Application2D.h"
#include <GLFW/glfw3.h>

#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"

#include "KeyboardBehaviour.h"
#include "FollowBehaviour.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	createWindow("A.I. Project", 1280, 720);

	m_spriteBatch = new SpriteBatch();


	m_nodeTex = new Texture("./bin/textures/Node.png");
	m_font = new Font("./bin/font/consolas.ttf", 32);

	// Setup the graph
	m_pGraph = new AI::Graph();

	const float STARTPOS = 50;
	Math::Vector2 pos;

	// Invert Y
	for (pos.Y = 720.0f - STARTPOS; pos.Y > 0; pos.Y -= NODESPACING)
	{
		for (pos.X = STARTPOS; pos.X < 1280.0f; pos.X += NODESPACING)
		{
			m_pGraph->AddNode(pos);
		}
	}

	auto nodeList = m_pGraph->GetNodes();

	// Connect all nodes near each other
	for each (auto node in nodeList)
	{
		std::vector<AI::Graph::Node*> nodes;
		m_pGraph->FindNodeInRange(nodes, node->m_vPosition, NODESPACING + 5);

		for each (auto node2 in nodes)
		{
			// Ensure it isn't adding itself as a connection
			if (node == node2)
				continue;

			// Ensure these 2 nodes aren't already connected
			bool alreadyConnected = false;
			for each (auto connection in node2->m_Connections)
			{
				if (connection.m_pConnectionNode == node)
				{
					alreadyConnected = true;
					break;
				}
			}

			if (!alreadyConnected)
				m_pGraph->AddConnection(node, node2);
		}
	}

	// Set up initial start and end nodes
	m_pStartNode = nodeList.front();
	m_pEndNode = nodeList.back();

	return true;
}

void Application2D::shutdown() {
	delete m_pGraph;
	delete m_nodeTex;
	delete m_font;
	delete m_spriteBatch;

	destroyWindow();
}

bool Application2D::update(float deltaTime) {
	
	// close the application if the window closes or we press escape
	if (hasWindowClosed() || isKeyPressed(GLFW_KEY_ESCAPE))
		return false;

	static bool updatePath = true;
	static bool updateStart = true;
	int x, y;
	this->getCursorPosition(x, y);
	Math::Vector2 mousePos = { (float)x, 720.0f - y };


	if (this->isMouseButtonPressed(0)) // Left mouse button was pressed
	{
		// Find nearest node
		std::vector<AI::Graph::Node*> nearestNodes;
		m_pGraph->FindNodeInRange(nearestNodes, mousePos, 20.0f);

		// Update start/end nodes to the new node
		if (nearestNodes.size() != 0)
		{
			auto nearest = nearestNodes[0];

			// We make sure start and end nodes are not the same node
			if (nearest != m_pStartNode && nearest != m_pEndNode)
			{
				if (updateStart)
					m_pStartNode = nearest;
				else
					m_pEndNode = nearest;

				updateStart = !updateStart;
				updatePath = true;
			}
		}
	}
	else if (this->isMouseButtonPressed(1)) // Right mouse button was pressed
	{
		// Find nearest node
		std::vector<AI::Graph::Node*> nearestNodes;
		m_pGraph->FindNodeInRange(nearestNodes, mousePos, 20.0f);

		if (nearestNodes.size() != 0)
		{
			auto nearest = nearestNodes[0];

			m_pGraph->RemoveNode(nearest);

			// If nearest is the start or end nodes, update them
			if (nearest == m_pStartNode)
				m_pStartNode = m_pGraph->GetNodes().front();
			else if (nearest == m_pEndNode)
				m_pEndNode = m_pGraph->GetNodes().back();

			updatePath = true;
		}
	}

	if (updatePath)
	{
		// Do pathfinding
		std::list<AI::Graph::Node*> path;
		AI::PathFinder::AStar(m_pStartNode, m_pEndNode, path);

		// Add path nodes to path list, but first clear the current list
		m_Path.clear();
		while (path.size() > 1) // If we are left with 1 node, we are done
		{
			auto currentNode = path.front();
			path.pop_front();
			m_Path.push_back({ currentNode, path.front() });
		}
		updatePath = false;
	}

	// the applciation closes if we return false
	return true;
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_spriteBatch->begin();


	auto nodes = m_pGraph->GetNodes();

	// Draw Connections
	std::list<std::pair<AI::Graph::Node*, AI::Graph::Node*>> drawnConnections;
	for each (auto node in nodes)
	{
		for each (auto connection in node->m_Connections)
		{
			bool hasDrawn = false;
			for each (auto pair in drawnConnections)
			{
				if (connection.m_pConnectionNode == pair.first || node == pair.first)
					if (connection.m_pConnectionNode == pair.second || node == pair.second)
						hasDrawn = true;
			}

			// Handle drawing the path
			for each (auto pair in m_Path)
			{
				if (connection.m_pConnectionNode == pair.first || node == pair.first)
					if (connection.m_pConnectionNode == pair.second || node == pair.second)
					{
						// This connection is part of the path
						m_spriteBatch->setSpriteColor(0.7f, 0.7f, 0.0f, 1.0f);

						// Draw the connection
						m_spriteBatch->drawLine(node->m_vPosition.X, node->m_vPosition.Y, connection.m_pConnectionNode->m_vPosition.X, connection.m_pConnectionNode->m_vPosition.Y, 4, 10);

						// Mark that is has been drawn
						hasDrawn = true;
					}
			}

			if (!hasDrawn)
			{
				m_spriteBatch->setSpriteColor(0.5f, 0.5f, 0.5f, 1.0f);

				// Draw the connection
				m_spriteBatch->drawLine(node->m_vPosition.X, node->m_vPosition.Y, connection.m_pConnectionNode->m_vPosition.X, connection.m_pConnectionNode->m_vPosition.Y, 1, 10);

				// Add to the drawn list
				drawnConnections.push_back({ node, connection.m_pConnectionNode });
			}
		}
	}

	// Draw the nodes
	for each (auto node in nodes)
	{
		bool hasDrawn = false;

		// Draw the Start and End nodes
		if (m_pStartNode == node)
		{
			m_spriteBatch->setSpriteColor(0.4f, 0.8f, 0.2f, 1.0f);
			m_spriteBatch->drawSprite(m_nodeTex, node->m_vPosition.X, node->m_vPosition.Y, 30, 30, 0, 5);
			hasDrawn = true;
		}
		else if (m_pEndNode == node)
		{
			m_spriteBatch->setSpriteColor(0.8f, 0.6f, 0.0f, 1.0f);
			m_spriteBatch->drawSprite(m_nodeTex, node->m_vPosition.X, node->m_vPosition.Y, 30, 30, 0, 5);
			hasDrawn = true;
		}

		// Draw any nodes in the path
		for each (auto pair in m_Path)
		{
			// We only draw the first of the pair
			if (pair.first == node)
			{
				m_spriteBatch->setSpriteColor(0.7f, 0.7f, 0.0f, 1.0f);
				m_spriteBatch->drawSprite(m_nodeTex, node->m_vPosition.X, node->m_vPosition.Y, 25, 25, 0, 5);

				// Mark that we have drawn this node
				hasDrawn = true;
			}
		}

		// Draw the rest of the nodes
		if (!hasDrawn)
		{
			m_spriteBatch->setSpriteColor(0.4f, 0.6f, 0.8f, 1.0f);
			m_spriteBatch->drawSprite(m_nodeTex, node->m_vPosition.X, node->m_vPosition.Y, 16, 16, 0, 5);
		}
	}

	// TODO: Draw path

	// done drawing sprites
	m_spriteBatch->end();	
}