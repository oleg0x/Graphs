#include "shortest_paths.h"
#include <limits>

using namespace std;



DijkstraShortestPaths::DijkstraShortestPaths(const DirectedEdgeWeightedGraph& graph, VertexType s)
	: graph_ {graph}
	, init_v_ {s}
	, edge_to_(graph_.Order())
	, dist_to_(graph_.Order(), numeric_limits<double>::infinity())
	, pq_(graph_.Order())
{
	dist_to_[init_v_] = 0.0;
	pq_.Insert(init_v_, 0.0);
	while ( !pq_.Empty() )
	{
		int v = pq_.DelMin();
		for ( const Edge& e : graph_.AdjacentVertices(v, 0) )  Relax(e);
	}
}



bool DijkstraShortestPaths::HasPathTo(VertexType v) const
{
	return dist_to_[v] < numeric_limits<double>::infinity();
}



double DijkstraShortestPaths::DistanceTo(VertexType v) const
{
	return dist_to_[v];
}



const std::deque<Edge>& DijkstraShortestPaths::PathTo(VertexType v)
{
	path_.clear();
	if ( HasPathTo(v) )
		for ( Edge e = edge_to_[v]; e != Edge(0, 0, 0.0); e = edge_to_[e.v] )
			path_.push_front(e);
	return path_;
}



void DijkstraShortestPaths::Relax(const Edge& e)
{
	if ( dist_to_[e.v] + e.weight < dist_to_[e.w] )
	{
		dist_to_[e.w] = dist_to_[e.v] + e.weight;
		edge_to_[e.w] = e;
		if ( pq_.Contains(e.w) )  pq_.DecreaseElem(e.w, dist_to_[e.w]);
		else  pq_.Insert(e.w, dist_to_[e.w]);
	}
}
