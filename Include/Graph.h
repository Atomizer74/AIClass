#pragma once

#include <MathLib.h>

#include <list>
#include <vector>


namespace AI
{

	class Graph
	{
	private:
		// Copy constructor
		Graph(const Graph& refGraph) = delete;
		// Copy Assignment Operator
		Graph& operator=(const Graph& refGraph) = delete;

	public:
		class Node;

		class Edge
		{
		public:
			Node* m_pConnectionNode;

			float m_fCost;

			Edge() : Edge(nullptr) {}
			Edge(Node* pNode) : Edge(pNode, 1.0f) {}
			Edge(Node* pNode, float fCost) : m_pConnectionNode(pNode), m_fCost(fCost) {}
		};

		class Node
		{
		public:
			// Position for gameplay purposes
			Math::Vector2 m_vPosition;

			std::list<Edge> m_Connections;

			Node() {}
			Node(const Math::Vector2& refPos) : m_vPosition(refPos) {}
		};

	public:
		// Default Constructor
		Graph();
		// Destructor
		~Graph();

		// Adds a node to our graph
		Node* AddNode(const Math::Vector2& refPos = { 0.0f, 0.0f });
		void RemoveNode(Node* pNode);

		// Connects 2 nodes in our graph
		void AddConnection(Node* pNodeA, Node* pNodeB, float fCost = 1.0f);

		void FindNodeInRange(std::vector<Node*> &outNodes, const Math::Vector2& refPos, float fRadius);

		inline std::list<Node*> GetNodes() { return m_NodeList; }

	private:
		std::list<Node*> m_NodeList;
	};
}