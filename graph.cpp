#include "graph.h"
#include <iostream>
#include <fstream>

using namespace std;


//-------------------------------------------------------------------


ostream& operator <<(ostream& os, const Edge& e)
{
	return os << "(" << e.v << ", " << e.w << ", " << e.weight << ")";
}



bool operator ==(const Edge& d, const Edge& e)
{
	return ( d.v == e.v && d.w == e.w && d.weight == e.weight );
}



bool operator >(const Edge& d, const Edge& e)
{
	return ( d.weight > e.weight );
}


//-------------------------------------------------------------------



Graph::Graph(uint32_t v_number)
	: vertices_number_ {v_number}
	, edges_number_ {0}
{}



Graph::Graph(const char* file_name)
{
	file_.open(file_name);
	if ( !file_.is_open() )
	{
		vertices_number_ = 0;
		edges_number_ = 0;
		cout << "Failed to open " << file_name 
		     << "! Empty graph created." << '\n';
	}
	else
		file_ >> vertices_number_ >> edges_number_;
}



Graph::~Graph()
{}



uint32_t Graph::Order() const
{
	return vertices_number_;
}



uint32_t Graph::Size() const
{
	return edges_number_;
}


//-------------------------------------------------------------------


UnweightedGraph::UnweightedGraph(uint32_t v_number)
	: Graph(v_number)
	, adj_(vertices_number_)
{}



UnweightedGraph::UnweightedGraph(const char* file_name)
	: Graph(file_name)
	, adj_(vertices_number_)
{}



const list<VertexType>& UnweightedGraph::AdjacentVertices(VertexType v) const
{
	return adj_[v];
}



const std::list<Edge>& UnweightedGraph::AdjacentVertices(VertexType, uint8_t) const
{
	throw runtime_error("const list<Edge>& UnweightedGraph::AdjacentVertices(\
VertexType, uint8_t) can not be called from UnweightedGraph!");
}



void UnweightedGraph::PrintAdjacencyList() const
{
	cout << "Adjacency list:\n";
	for ( VertexType i = 0; i < vertices_number_; ++i )
	{
		cout << i << ':';
		for ( VertexType v : adj_[i] )  cout << ' ' << v;
		cout << '\n';
	}
}


//-------------------------------------------------------------------


UndirectedUnweightedGraph::UndirectedUnweightedGraph(uint32_t v_number)
	: UnweightedGraph(v_number)
{}



UndirectedUnweightedGraph::UndirectedUnweightedGraph(const char* file_name)
	: UnweightedGraph(file_name)
{
	VertexType v1, v2;
	for ( uint32_t i = 0; i < edges_number_; ++i )
	{
		file_ >> v1 >> v2;
		adj_[v1].push_back(v2);
		adj_[v2].push_back(v1);
	}
}



bool UndirectedUnweightedGraph::InsertEdge(VertexType v, VertexType w)
{
	if ( v < vertices_number_ && w < vertices_number_ )
	{
		adj_[v].push_back(w);  // Parallel edges and self-loops are allowed
		adj_[w].push_back(v);
		++edges_number_;
		return true;
	}
	return false;
}



bool UndirectedUnweightedGraph::InsertEdge(const Edge& e)
{
	return InsertEdge(e.v, e.w);
}



bool UndirectedUnweightedGraph::EraseEdge(VertexType v, VertexType w)
{
	uint32_t n;
	if ( v < vertices_number_ && w < vertices_number_ &&
		(n = adj_[v].remove(w) + adj_[w].remove(v)) > 0 )
	{
		edges_number_ -= n/2;
		return true;
	}
	return false;
}



bool UndirectedUnweightedGraph::EraseEdge(const Edge& e)
{
	return EraseEdge(e.v, e.w);
}


//-------------------------------------------------------------------


DirectedUnweightedGraph::DirectedUnweightedGraph(uint32_t v_number)
	: UnweightedGraph(v_number)
{}



DirectedUnweightedGraph::DirectedUnweightedGraph(const char* file_name)
	: UnweightedGraph(file_name)
{
	VertexType v1, v2;
	for ( uint32_t i = 0; i < edges_number_; ++i )
	{
		file_ >> v1 >> v2;
		adj_[v1].push_back(v2);
	}
}



bool DirectedUnweightedGraph::InsertEdge(VertexType v, VertexType w)
{
	if ( v < vertices_number_ && w < vertices_number_ )
	{
		adj_[v].push_back(w);  // Parallel edges and self-loops are allowed
		++edges_number_;
		return true;
	}
	return false;
}



bool DirectedUnweightedGraph::InsertEdge(const Edge& e)
{
	return InsertEdge(e.v, e.w);
}



bool DirectedUnweightedGraph::EraseEdge(VertexType v, VertexType w)
{
	uint32_t n;
	if ( v < vertices_number_ && w < vertices_number_ &&
		(n = adj_[v].remove(w)) > 0 )
	{
		edges_number_ -= n;
		return true;
	}
	return false;
}



bool DirectedUnweightedGraph::EraseEdge(const Edge& e)
{
	return EraseEdge(e.v, e.w);
}


//-------------------------------------------------------------------


EdgeWeightedGraph::EdgeWeightedGraph(uint32_t v_number)
	: Graph(v_number)
	, adj_(vertices_number_)
{}



EdgeWeightedGraph::EdgeWeightedGraph(const char* file_name)
	: Graph(file_name)
	, adj_(vertices_number_)
{}



const std::list<VertexType>& EdgeWeightedGraph::AdjacentVertices(VertexType) const
{
	throw runtime_error("const std::list<VertexType>& AdjacentVertices(\
VertexType) can not be called from EdgeWeightedGraph!");
}



const list<Edge>& EdgeWeightedGraph::AdjacentVertices(VertexType v, uint8_t) const
{
	return adj_[v];
}



void EdgeWeightedGraph::PrintAdjacencyList() const
{
	cout << "Adjacency list:\n";
	for ( uint32_t i = 0; i < vertices_number_; ++i )
	{
		cout << i << ':';
		for ( const Edge& edge : adj_[i] )  cout << ' ' << edge;
		cout << '\n';
	}
}


//-------------------------------------------------------------------


UndirectedEdgeWeightedGraph::UndirectedEdgeWeightedGraph(uint32_t v_number)
	: EdgeWeightedGraph(v_number)
{}



UndirectedEdgeWeightedGraph::UndirectedEdgeWeightedGraph(const char* file_name)
	: EdgeWeightedGraph(file_name)
{
	Edge edge;
	for ( uint32_t i = 0; i < edges_number_; ++i )
	{
		file_ >> edge.v >> edge.w >> edge.weight;
		adj_[edge.v].push_back(edge);
		adj_[edge.w].push_back(edge);
	}
}



bool UndirectedEdgeWeightedGraph::InsertEdge(VertexType v, VertexType w)
{
	return InsertEdge({v, w, 0.0});
}



bool UndirectedEdgeWeightedGraph::InsertEdge(const Edge& edge)
{
	if ( edge.v < vertices_number_ && edge.w < vertices_number_ )
	{
		adj_[edge.v].push_back(edge);  // Parallel edges and self-loops are allowed
		adj_[edge.w].push_back(edge);
		++edges_number_;
		return true;
	}
	return false;
}



bool UndirectedEdgeWeightedGraph::EraseEdge(VertexType v, VertexType w)
{
	return EraseEdge({v, w, 0.0});
}



bool UndirectedEdgeWeightedGraph::EraseEdge(const Edge& edge)
{
	uint32_t n;
	if ( edge.v < vertices_number_ && edge.w < vertices_number_ &&
		(n = adj_[edge.v].remove(edge) + adj_[edge.w].remove(edge)) > 0 )
	{
		edges_number_ -= n/2;
		return true;
	}
	return false;
}


//-------------------------------------------------------------------


DirectedEdgeWeightedGraph::DirectedEdgeWeightedGraph(uint32_t v_number)
	: EdgeWeightedGraph(v_number)
{}



DirectedEdgeWeightedGraph::DirectedEdgeWeightedGraph(const char* file_name)
	: EdgeWeightedGraph(file_name)
{
	Edge edge;
	for ( uint32_t i = 0; i < edges_number_; ++i )
	{
		file_ >> edge.v >> edge.w >> edge.weight;
		adj_[edge.v].push_back(edge);
	}
}



bool DirectedEdgeWeightedGraph::InsertEdge(VertexType v, VertexType w)
{
	return InsertEdge({v, w, 0.0});
}



bool DirectedEdgeWeightedGraph::InsertEdge(const Edge& edge)
{
	if ( edge.v < vertices_number_ && edge.w < vertices_number_ )
	{
		adj_[edge.v].push_back(edge);  // Parallel edges and self-loops are allowed
		++edges_number_;
		return true;
	}
	return false;
}



bool DirectedEdgeWeightedGraph::EraseEdge(VertexType v, VertexType w)
{
	return EraseEdge({v, w, 0.0});
}



bool DirectedEdgeWeightedGraph::EraseEdge(const Edge& edge)
{
	uint32_t n;
	if ( edge.v < vertices_number_ && edge.w < vertices_number_ &&
		(n = adj_[edge.v].remove(edge)) > 0 )
	{
		edges_number_ -= n;
		return true;
	}
	return false;
}
