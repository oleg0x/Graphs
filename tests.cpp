#include "graph.h"
#include "paths.h"
#include "connected_components.h"
#include "cycles.h"
#include "topological_order.h"
#include "prim_mst.h"
#include "shortest_paths.h"

#include <array>
#include <cassert>
#include <iostream>
#include <type_traits>

using namespace std;



template <typename T>
void PrintIterable(T& cont)
{
	if ( cont.empty() )  cout << "Empty";
	for ( auto x : cont )  cout << x << " ";
	cout << '\n';
}



void TestGraph()
{
	cout << "---------- " << __func__ << " ----------\n\n";

	array<Graph*, 4> graphs;
	graphs[0] = new UndirectedUnweightedGraph("graph_samples/undunwgraph1.txt");
	graphs[1] = new DirectedUnweightedGraph("graph_samples/dunwgraph1.txt");
	graphs[2] = new UndirectedEdgeWeightedGraph("graph_samples/undwgraph1.txt");
	graphs[3] = new DirectedEdgeWeightedGraph("graph_samples/dwgraph1.txt");

	array<uint32_t, 4> a1 {15, 24, 18, 17};
	array<uint32_t, 4> a2 {13, 24, 17, 16};

	for ( uint8_t i = 0; i < 4; ++i )
	{
		Graph* p = graphs[i];

		cout << "Order: " << p->Order() << ", Size: " << p->Size() << '\n';
		p->PrintAdjacencyList();
		cout << "Adjacent vertices for 4:\n";

		try {
			PrintIterable(p->AdjacentVertices(4));
		}
		catch ( runtime_error& ex )
		{
			cout << ex.what() << '\n';
		}

		try {
			PrintIterable(p->AdjacentVertices(4, 0));
		}
		catch ( runtime_error& ex )
		{
			cout << ex.what() << '\n';
		}

		cout << "Insert edge: " << p->InsertEdge(2, 4) << ' '
		     << p->InsertEdge({3, 5, 1.111}) << '\n';
		cout << "Order: " << p->Order() << ", Size: " << p->Size() << '\n';
		assert( p->Size() == a1[i] );
		cout << "Erase edge: " << p->EraseEdge(7, 8) << ' '
		     << p->EraseEdge({4, 5, 0.35}) << '\n';
		cout << "Order: " << p->Order() << ", Size: " << p->Size() << '\n';
		assert( p->Size() == a2[i] );

		p->PrintAdjacencyList();
		cout << '\n';
	}

	for ( Graph* p : graphs )  delete p;
}



void TestUndUnwGraphs()
{
	cout << "---------- " << __func__ << " ----------\n\n";

	UndirectedUnweightedGraph graph1("graph_samples/undunwgraph1.txt");

	Paths paths1(graph1, 3, SearchType::DFS);
	cout << "Path from 3 to 0: ";
	PrintIterable(paths1.PathTo(0));

	Paths paths2(graph1, 3, SearchType::BFS);
	cout << "Shortest path from 3 to 0: ";
	PrintIterable(paths2.PathTo(0));

	ConnectedComponents cc(graph1);
	cout << "\nNumber of connected components: " << cc.Count() << '\n'
	     << "Vertex 2: component id " << cc.GetComponentId(2) << '\n'
	     << "Vertex 7: component id " << cc.GetComponentId(7) << '\n'
	     << "Vertex 12: component id " << cc.GetComponentId(12) << '\n';
	assert( cc.Count() == 3 );

	cout << "\nVertices 2 and 5 are connected: "
	     << cc.AreConnected(2, 5) << '\n'
	     << "Vertices 7 and 9 are connected: "
	     << cc.AreConnected(7, 9) << '\n';
	assert( cc.AreConnected(2, 5) == true && cc.AreConnected(7, 9) == false );

	UndirectedCycle cycle1(graph1);
	cout << "\nGraph #1 has a cycle? " << cycle1.HasCycle() << '\n';
	UndirectedUnweightedGraph graph2("graph_samples/undunwgraph2.txt");
	UndirectedCycle cycle2(graph2);
	cout << "Graph #2 has a cycle? " << cycle2.HasCycle() << "\n\n";
	assert( cycle1.HasCycle() == true && cycle2.HasCycle() == false );
}



void TestDUnwGraphs()
{
	cout << "---------- " << __func__ << " ----------\n\n";

	DirectedUnweightedGraph graph1("graph_samples/dunwgraph1.txt");

	Paths paths1(graph1, 0, SearchType::DFS);
	cout << "Path from 0 to 2: ";
	PrintIterable(paths1.PathTo(2));
//	paths1.DebugPrint();

	Paths paths2(graph1, 0, SearchType::BFS);
	cout << "Shortest path from 0 to 2: ";
	PrintIterable(paths2.PathTo(2));
	paths2.DebugPrint();

	DirectedUnweightedGraph graph2("graph_samples/dunwgraph2.txt");
	DirectedCycle dc1(graph2);
	cout << "\nGraph #2 has a cycle? " << dc1.HasCycle() << '\n';
	assert( dc1.HasCycle() == true );
	cout << "Cycle vertices: ";
	PrintIterable(dc1.GetCycle());

	DirectedUnweightedGraph graph3("graph_samples/dunwgraph3.txt");
	TopologicalOrder topol_order1(graph3);
	cout << "\nTopological order: ";
	PrintIterable(topol_order1.GetOrder());

	DirectedUnweightedGraph graph4("graph_samples/dunwgraph4.txt");
//	digraph4.PrintAdjacencyList();
	TopologicalOrder topol_order2(graph4);
	cout << "Topological order: ";
	PrintIterable(topol_order2.GetOrder());

	TopologicalOrder topol_order3(graph2);
	cout << "Topological order (containes cycle): ";
	PrintIterable(topol_order3.GetOrder());
	cout << "Is DAG: " << topol_order3.IsDAG() << "\n\n";
	assert( topol_order3.IsDAG() == false );
}



void TestUndWGraph()
{
	cout << "---------- " << __func__ << " ----------\n\n";

	UndirectedEdgeWeightedGraph graph1("graph_samples/undwgraph1.txt");
	LazyPrimMST mst(graph1);
	const deque<Edge>& d = mst.GetMST();
	cout << "Size of MST: " << d.size() << "\n";
	assert( d.size() == 7 );
	cout << "Edges of MST: ";
	PrintIterable(d);
	cout << '\n';
}



void TestDWGraph()
{
	cout << "---------- " << __func__ << " ----------\n\n";

	DirectedEdgeWeightedGraph graph1("graph_samples/dwgraph1.txt");
	DijkstraShortestPaths dsp(graph1, 0);
	cout << "ShortestPaths:\n";
	for ( VertexType v = 0; v < graph1.Order(); ++v )
	{
		cout << 0 << " to " << v << " (" << dsp.DistanceTo(v) << "): ";
		for ( const Edge& e : dsp.PathTo(v) )
			cout << e << " ";
		cout << '\n';
	}
}
