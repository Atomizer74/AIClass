#include "PathFinder.h"


namespace AI
{


	void PathFinder::Dijkstras(Graph::Node* pStartNode, Graph::Node* pEndNode, std::list<Graph::Node*>& outPath)
	{
		std::list<SearchNode*> openList;
		std::list<SearchNode*> closedList;

		SearchNode* endNode = nullptr;
		SearchNode* startNode = new SearchNode(pStartNode);
		openList.push_back(startNode);

		while (!openList.empty())
		{
			openList.sort([](SearchNode* a, SearchNode* b) { return (a->gScore < b->gScore); });

			SearchNode* currentNode = openList.front();

			if (currentNode->node == pEndNode)
			{
				endNode = currentNode;
				break;
			}

			openList.pop_front();
			closedList.push_back(currentNode);

			for each (auto edge in currentNode->node->m_Connections)
			{
				SearchNode* connection = new SearchNode(edge.m_pConnectionNode);

				// Add connection to open list if not in closed list
				bool inClosedList = false;
				for each (auto n in closedList)
				{
					if (n->node == edge.m_pConnectionNode)
					{
						inClosedList = true;
						break;
					}
				}

				if (inClosedList)
					continue;

				bool inOpenList = false;
				for each (auto n in openList)
				{
					if (n->node == connection->node)
					{
						inOpenList = true;
						break;
					}
				}

				// If not in the open list, we need to add it
				if (!inOpenList)
				{
					connection->gScore = currentNode->gScore + edge.m_fCost;
					connection->parent = currentNode;
					openList.push_back(connection);
					continue;
				}

				// If it is in the open list, calculate a new score and keep the lowest
				float newScore = currentNode->gScore + edge.m_fCost;
				if (newScore < connection->gScore)
				{
					connection->gScore = newScore;
					connection->parent = currentNode;
				}
			}
		}

		// Calculate Path
		SearchNode* currentNode = endNode;
		while (currentNode != nullptr)
		{
			outPath.push_back(currentNode->node);
			currentNode = currentNode->parent;
		}
	}


	void PathFinder::AStar(Graph::Node* pStartNode, Graph::Node* pEndNode, std::list<Graph::Node*>& outPath)
	{
		std::list<SearchNode*> openList;
		std::list<SearchNode*> closedList;

		SearchNode* endNode = nullptr;
		SearchNode* startNode = new SearchNode(pStartNode);
		openList.push_back(startNode);
		startNode->gScore = 0;
		startNode->hScore = (startNode->node->m_vPosition - pEndNode->m_vPosition).Magnitude();
		startNode->fScore = startNode->hScore;

		while (!openList.empty())
		{
			openList.sort([](SearchNode* a, SearchNode* b) { return (a->fScore < b->fScore); });

			SearchNode* currentNode = openList.front();

			if (currentNode->node == pEndNode)
			{
				endNode = currentNode;
				break;
			}

			openList.pop_front();
			closedList.push_back(currentNode);

			for each (auto edge in currentNode->node->m_Connections)
			{
				bool inClosedList = false;
				for each (auto n in closedList)
				{
					if (n->node == edge.m_pConnectionNode)
					{
						inClosedList = true;
						break;
					}
				}

				if (inClosedList)
					continue;

				SearchNode* connection = new SearchNode(edge.m_pConnectionNode);

				float tentative_gScore = currentNode->gScore + (edge.m_fCost * (currentNode->node->m_vPosition - connection->node->m_vPosition).Magnitude());

				bool inOpenList = false;
				for each (auto n in openList)
				{
					if (n->node == edge.m_pConnectionNode)
					{
						inOpenList = true;

						// If this node is in the open list, we want to be using it instead of our created node
						delete connection;
						connection = n;
						break;
					}
				}

				if (!inOpenList)
					openList.push_back(connection);
				else if (tentative_gScore >= connection->gScore)
					continue; // This is not a better path

				// This path is the best until now
				connection->parent = currentNode;
				connection->gScore = tentative_gScore;
				connection->hScore = (connection->node->m_vPosition - pEndNode->m_vPosition).Magnitude();
				connection->fScore = connection->gScore + connection->hScore;
			}
		}

		// Calculate Path
		SearchNode* currentNode = endNode;
		while (currentNode != nullptr)
		{
			outPath.push_back(currentNode->node);
			currentNode = currentNode->parent;
		}
	}

}