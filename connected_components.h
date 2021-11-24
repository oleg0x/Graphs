#pragma once

#include "graph.h"

using IdType = uint32_t;



class ConnectedComponents
{
public:
	explicit ConnectedComponents(const UnweightedGraph& graph);
	bool AreConnected(VertexType v, VertexType w) const;
	uint32_t Count() const;  // Number of connected components
	IdType GetComponentId(VertexType v) const;
	
private:
	void DepthFirstSearch(VertexType s);

	const UnweightedGraph& graph_;
	std::vector<bool> marked_;
	std::vector<IdType> component_id_;
	uint32_t count_ = 0;
};
