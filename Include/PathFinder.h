#pragma once

#include "Graph.h"
#include <list>

namespace AI
{
	// The main purpose of this class is to
	// find paths between 2 nodes on a graph
	class PathFinder
	{
	private:
		class SearchNode
		{
		public:
			Graph::Node* node;

			SearchNode* parent;
			int degreeOfSeparation;
			float gScore;
			float hScore;
			float fScore;


			SearchNode() : SearchNode(nullptr) {}
			SearchNode(Graph::Node* pNode) : SearchNode(pNode, nullptr) {}
			SearchNode(Graph::Node* pNode, SearchNode* pParent) : node(pNode), parent(pParent), degreeOfSeparation(0), gScore(999999), hScore(0.0f), fScore(999999) {}
		};
	private:
		PathFinder() = delete; // For now, we don't create instances of this class

	public:

		static void Dijkstras(Graph::Node* pStartNode, Graph::Node* pEndNode, std::list<Graph::Node*>& outPath);
		static void AStar(Graph::Node* pStartNode, Graph::Node* pEndNode, std::list<Graph::Node*>& outPath);
	};
}