#pragma once

#include "graph.h"
#include <deque>
#include <vector>



class Cycle
{
public:
	Cycle(const UnweightedGraph& graph);
	virtual bool HasCycle() const = 0;
	virtual const std::deque<VertexType>& GetCycle() const = 0;

protected:
	const UnweightedGraph& graph_;
	std::vector<bool> marked_;
};



class UndirectedCycle : public Cycle
{
public:
	UndirectedCycle(const UndirectedUnweightedGraph& graph);
	bool HasCycle() const override;
	const std::deque<VertexType>& GetCycle() const override;

private:
	void DepthFirstSearch(VertexType v, VertexType u);

	bool has_cycle_ = false;
	std::deque<VertexType> cycle_;
};



class DirectedCycle : public Cycle
{
public:
	DirectedCycle(const DirectedUnweightedGraph& graph);
	bool HasCycle() const override;
	const std::deque<VertexType>& GetCycle() const override;

private:
	void DepthFirstSearch(VertexType v);

	std::vector<VertexType> edge_to_;
	std::vector<bool> on_stack_;    // Vertices on recursive call stack
	std::deque<VertexType> cycle_;  // Vertices on a cycle (if one exists)
};
