#pragma once

#include "graph.h"
#include "index_min_pq.h"
#include <deque>



class DijkstraShortestPaths
{
public:
	DijkstraShortestPaths(const DirectedEdgeWeightedGraph& graph, VertexType s);
	bool HasPathTo(VertexType v) const;
	double DistanceTo(VertexType v) const;
	const std::deque<Edge>& PathTo(VertexType v);

private:
	void Relax(const Edge& e);

	const DirectedEdgeWeightedGraph& graph_;
	VertexType init_v_;
	std::vector<Edge> edge_to_;
	std::vector<double> dist_to_;
	IndexMinPQ<double> pq_;
	std::deque<Edge> path_;
};
