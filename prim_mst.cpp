#include "prim_mst.h"



LazyPrimMST::LazyPrimMST (const UndirectedEdgeWeightedGraph& graph)
	: graph_ {graph}
	, marked_(graph_.Order(), false)
{
	Visit(0);
	while ( !pq_.empty() && mst_.size() < graph_.Order() - 1 )
	{
		Edge e = pq_.top();
		pq_.pop();
		if ( marked_[e.v] && marked_[e.w] )  continue;
		mst_.push_back(e);
		if ( !marked_[e.v] )  Visit(e.v);
		if ( !marked_[e.w] )  Visit(e.w);
	}
}



const std::deque<Edge>& LazyPrimMST::GetMST()
{
	return mst_;
}



void LazyPrimMST::Visit(VertexType u)
{
	marked_[u] = true;
	VertexType other;
	for ( const Edge& e : graph_.AdjacentVertices(u, 0) )
	{
		other = ( u == e.v ? e.w : e.v );
		if ( !marked_[other] )  pq_.push(e);
	}
}
