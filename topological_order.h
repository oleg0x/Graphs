#pragma once

#include "graph.h"
#include <deque>
#include <vector>



class TopologicalOrder
{
public:
	TopologicalOrder(const DirectedUnweightedGraph& graph);
	bool IsDAG() const;  // Directed Acyclic Graph
	const std::deque<VertexType>& GetOrder() const;

private:
	void DepthFirstSearch(VertexType v);

	const DirectedUnweightedGraph& graph_;
	std::vector<bool> marked_;
	std::deque<VertexType> reverse_post_;  // topological order
};
