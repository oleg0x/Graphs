#include "cycles.h"



Cycle::Cycle(const UnweightedGraph& graph)
	: graph_ {graph}
	, marked_(graph_.Order(), false)
{}


//-------------------------------------------------------------------


UndirectedCycle::UndirectedCycle(const UndirectedUnweightedGraph& graph)
	: Cycle(graph)
{
	for ( VertexType s = 0; s < graph_.Order(); ++s )
		if ( !marked_[s] )
			DepthFirstSearch(s, s);
}



bool UndirectedCycle::HasCycle() const
{
	return has_cycle_;
}



const std::deque<VertexType>& UndirectedCycle::GetCycle() const
{
	return cycle_;
}



void UndirectedCycle::DepthFirstSearch(VertexType v, VertexType u)
{
	marked_[v] = true;
	for ( VertexType w : graph_.AdjacentVertices(v) )
		if ( !marked_[w] )  DepthFirstSearch(w, v);
		else if ( w != u )  has_cycle_ = true;
}


//-------------------------------------------------------------------


DirectedCycle::DirectedCycle(const DirectedUnweightedGraph& graph)
	: Cycle(graph)
	, edge_to_(graph.Order(), 0)
	, on_stack_(graph.Order(), false)
{
	for ( VertexType s = 0; s < graph_.Order(); ++s )
		if ( !marked_[s] )
			DepthFirstSearch(s);
}



bool DirectedCycle::HasCycle() const
{
	return !cycle_.empty();
}



const std::deque<VertexType>& DirectedCycle::GetCycle() const
{
	return cycle_;
}



void DirectedCycle::DepthFirstSearch(VertexType v)
{
	on_stack_[v] = true;
	marked_[v] = true;

	for ( VertexType w : graph_.AdjacentVertices(v) )
		if ( HasCycle() )  return;
		else if ( !marked_[w] )
		{
			edge_to_[w] = v;
			DepthFirstSearch(w);
		}
		else if ( on_stack_[w] )
		{
			cycle_.clear();
			for ( VertexType x = v; x != w; x = edge_to_[x])
				cycle_.push_front(x);
			cycle_.push_front(w);
			cycle_.push_front(v);
		}
	on_stack_[v] = false;
}
