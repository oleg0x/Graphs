#pragma once

#include "graph.h"
#include <deque>
#include <vector>

enum struct SearchType : uint8_t {DFS, BFS};



class Paths
{
public:
	Paths(const UnweightedGraph& graph, VertexType s, SearchType st);
	bool HasPathTo(VertexType v) const;
	const std::deque<VertexType>& PathTo(VertexType v);
	void DebugPrint() const;

private:
	void DepthFirstSearch(VertexType s);
	void BreadthFirstSearch();  // Shortest paths from vertex_

	const UnweightedGraph& graph_;
	const VertexType vertex_;
	std::vector<bool> marked_;
	std::vector<VertexType> edge_to_;
	std::deque<VertexType> path_;
};
