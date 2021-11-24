#include "connected_components.h"



ConnectedComponents::ConnectedComponents(const UnweightedGraph& graph)
	: graph_ {graph}
	, marked_(graph.Order(), false)
	, component_id_(graph.Order())
{
	for ( VertexType v = 0; v < graph.Order(); ++v )
		if ( !marked_[v] )
		{
			DepthFirstSearch(v);
			++count_;
		}
}



void ConnectedComponents::DepthFirstSearch(VertexType v)
{
	marked_[v] = true;
	component_id_[v] = count_;
	for ( VertexType w : graph_.AdjacentVertices(v) )
		if ( !marked_[w] )
			DepthFirstSearch(w);
}



bool ConnectedComponents::AreConnected(VertexType v, VertexType w) const
{
	return (component_id_[v] == component_id_[w]);
}



uint32_t ConnectedComponents::Count() const
{
	return count_;
}



IdType ConnectedComponents::GetComponentId(VertexType v) const
{
	return component_id_[v];
}
