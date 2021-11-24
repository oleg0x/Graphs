#pragma once

#include "graph.h"
#include <deque>
#include <queue>



class LazyPrimMST  // Lazy version of Prim's minimum spanning tree
{
public:
	explicit LazyPrimMST (const UndirectedEdgeWeightedGraph& graph);
	const std::deque<Edge>& GetMST();

private:
	void Visit(VertexType v);

	const UndirectedEdgeWeightedGraph& graph_;
	std::vector<bool> marked_;
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq_;
	std::deque<Edge> mst_;
};
