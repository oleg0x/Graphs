#include "topological_order.h"
#include "cycles.h"



TopologicalOrder::TopologicalOrder(const DirectedUnweightedGraph& graph)
	: graph_ {graph}
{
	DirectedCycle dc(graph_);
	if ( !dc.HasCycle() )
	{
		marked_.resize(graph.Order(), false);
		for ( VertexType v = 0; v < graph_.Order(); ++v )
			if ( !marked_[v] )
				DepthFirstSearch(v);
	}
}



bool TopologicalOrder::IsDAG() const
{
	return !reverse_post_.empty();
}



const std::deque<VertexType>& TopologicalOrder::GetOrder() const
{
	return reverse_post_;
}



void TopologicalOrder::DepthFirstSearch(VertexType v)
{
	marked_[v] = true;
	for ( VertexType w : graph_.AdjacentVertices(v) )
		if ( !marked_[w] )
			DepthFirstSearch(w);
	reverse_post_.push_front(v);
}
