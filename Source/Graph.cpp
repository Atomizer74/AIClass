#include "Graph.h"


namespace AI
{

	Graph::Graph()
	{

	}

	Graph::~Graph()
	{
		for each (Node* node in m_NodeList)
			delete node;

		m_NodeList.clear();
	}


	Graph::Node* Graph::AddNode(const Math::Vector2& refPos)
	{
		m_NodeList.push_back(new Node(refPos));

		return m_NodeList.back();
	}

	void Graph::RemoveNode(Node* pNode)
	{
		if (pNode == nullptr)
			return;

		m_NodeList.remove(pNode);

		// Remove connections back to this node
		for each (Edge connection in pNode->m_Connections)
		{
			auto connections = connection.m_pConnectionNode->m_Connections;
			connection.m_pConnectionNode->m_Connections.clear();

			for each (auto edge in connections)
			{
				if (edge.m_pConnectionNode != pNode)
					connection.m_pConnectionNode->m_Connections.push_back(edge);
			}
		}
	}

	void Graph::AddConnection(Node* pNodeA, Node* pNodeB, float fCost)
	{
		// Don't add nullptr connections to our list
		if (pNodeA == nullptr || pNodeB == nullptr)
			return;

		pNodeA->m_Connections.push_back({ pNodeB, fCost });
		pNodeB->m_Connections.push_back({ pNodeA, fCost });
	}

	void Graph::FindNodeInRange(std::vector<Node*> &outNodes, const Math::Vector2& refPos, float fRadius)
	{
		for each (Node* node in m_NodeList)
			// Add the node if the distance between them is less then the radius
			if ((node->m_vPosition - refPos).Magnitude() <= fRadius)
				outNodes.push_back(node);
	}


}