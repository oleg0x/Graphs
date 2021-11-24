/******************************************************************************
 * Adjacency-list graph representation. Maintain vertex-indexed vector of 
 * lists.
 *****************************************************************************/ 
#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using VertexType = uint32_t;  // Should be an integer type


//---------------------------------------------------------


struct Edge
{
	VertexType v;		// from, if directed
	VertexType w;		// to,   if directed
	double weight;
};

std::ostream& operator <<(std::ostream& os, const Edge& e);
bool operator ==(const Edge& d, const Edge& e);
bool operator  >(const Edge& d, const Edge& e);


//---------------------------------------------------------


class Graph  // Virtual base class
{
public:
	explicit Graph(uint32_t v_number);
	explicit Graph(const char* file_name);
	virtual ~Graph();
	
	uint32_t Order() const;  // The order of a graph is its number of vertices |V|
	uint32_t Size() const;   // The size of a graph is its number of edges |E|

//	bool InsertVertex(VertexType v);
//	bool EraseVertex(VertexType v);

	bool IsAdjacent(VertexType v, VertexType w) const;
	virtual void PrintAdjacencyList() const = 0;

	virtual const std::list<VertexType>& AdjacentVertices(VertexType v) const = 0;
	virtual const std::list<Edge>&       AdjacentVertices(VertexType v, uint8_t) const = 0;

	virtual bool InsertEdge(VertexType v, VertexType w) = 0;
	virtual bool InsertEdge(const Edge& edge) = 0;

	virtual bool EraseEdge(VertexType v, VertexType w) = 0;
	virtual bool EraseEdge(const Edge& edge) = 0;

protected:
	std::ifstream file_;
	uint32_t vertices_number_;
	uint32_t edges_number_;
};


//---------------------------------------------------------


class UnweightedGraph : public Graph
{
public:
	explicit UnweightedGraph(uint32_t v_number);
	explicit UnweightedGraph(const char* file_name);

	const std::list<VertexType>& AdjacentVertices(VertexType v) const override;
	const std::list<Edge>&       AdjacentVertices(VertexType v, uint8_t) const override;

	void PrintAdjacencyList() const override;

protected:
	std::vector<std::list<VertexType>> adj_;
};



class UndirectedUnweightedGraph : public UnweightedGraph
{
public:
	explicit UndirectedUnweightedGraph(uint32_t v_number);
	explicit UndirectedUnweightedGraph(const char* file_name);

	bool InsertEdge(VertexType v, VertexType w) override;
	bool InsertEdge(const Edge& edge) override;

	bool EraseEdge(VertexType v, VertexType w) override;
	bool EraseEdge(const Edge& edge) override;
};



class DirectedUnweightedGraph : public UnweightedGraph
{
public:
	explicit DirectedUnweightedGraph(uint32_t v_number);
	explicit DirectedUnweightedGraph(const char* file_name);

	bool InsertEdge(VertexType v, VertexType w) override;
	bool InsertEdge(const Edge& edge) override;

	bool EraseEdge(VertexType v, VertexType w) override;
	bool EraseEdge(const Edge& edge) override;

//	void Reverse();
};


//---------------------------------------------------------


class EdgeWeightedGraph : public Graph
{
public:
	explicit EdgeWeightedGraph(uint32_t v_number);
	explicit EdgeWeightedGraph(const char* file_name);

	const std::list<VertexType>& AdjacentVertices(VertexType v) const override;
	const std::list<Edge>&       AdjacentVertices(VertexType v, uint8_t) const override;

	void PrintAdjacencyList() const override;

protected:
	std::vector<std::list<Edge>> adj_;
};



class UndirectedEdgeWeightedGraph : public EdgeWeightedGraph
{
public:
	explicit UndirectedEdgeWeightedGraph(uint32_t v_number);
	explicit UndirectedEdgeWeightedGraph(const char* file_name);

	bool InsertEdge(VertexType v, VertexType w) override;
	bool InsertEdge(const Edge& edge) override;

	bool EraseEdge(VertexType v, VertexType w) override;
	bool EraseEdge(const Edge& edge) override;
};



class DirectedEdgeWeightedGraph : public EdgeWeightedGraph
{
public:
	explicit DirectedEdgeWeightedGraph(uint32_t v_number);
	explicit DirectedEdgeWeightedGraph(const char* file_name);

	bool InsertEdge(VertexType v, VertexType w) override;
	bool InsertEdge(const Edge& edge) override;

	bool EraseEdge(VertexType v, VertexType w) override;
	bool EraseEdge(const Edge& edge) override;
};
