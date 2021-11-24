#include "graph.h"
#include "paths.h"
#include <iostream>
#include <queue>

using namespace std;



Paths::Paths(const UnweightedGraph& graph, VertexType s, SearchType st)
	: graph_ {graph}, vertex_ {s}
	, marked_(graph.Order(), false)
	, edge_to_(graph.Order(), 0)
{
	st == SearchType::DFS ? DepthFirstSearch(vertex_) : BreadthFirstSearch();
}



bool Paths::HasPathTo(VertexType v) const
{
	return marked_[v];
}



const deque<VertexType>& Paths::PathTo(VertexType v)
{
	if ( HasPathTo(v) )
	{
		for ( VertexType x = v; x != vertex_; x = edge_to_[x] )
			path_.push_front(x);
		path_.push_front(vertex_);
	}
	return path_;
}



void Paths::DebugPrint() const
{
	cout << "\nVertex\tmarked_[] edge_to_[]\n";
	for ( uint32_t i = 0; i < graph_.Order(); ++i )
		cout << i << "\t" << marked_[i] << "\t  " << edge_to_[i] << '\n';
}



void Paths::DepthFirstSearch(VertexType s)
{
	marked_[s] = true;
	for ( VertexType w : graph_.AdjacentVertices(s) )
		if ( !marked_[w] )
		{
			DepthFirstSearch(w);
			edge_to_[w] = s;
		}
}



void Paths::BreadthFirstSearch()
{
	marked_.clear();
	edge_to_.clear();
	queue<VertexType> qu;
	qu.push(vertex_);
	marked_[vertex_] = true;
	while ( !qu.empty() )
	{
		VertexType v = qu.front();
		qu.pop();
		for ( VertexType w : graph_.AdjacentVertices(v) )
			if ( !marked_[w] )
			{
				qu.push(w);
				marked_[w] = true;
				edge_to_[w] = v;
			}
	}
}
