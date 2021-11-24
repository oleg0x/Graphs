#include <iostream>

void TestGraph();
void TestUndUnwGraphs();
void TestDUnwGraphs();
void TestUndWGraph();
void TestDWGraph();



int main()
{
	std::cout << std::boolalpha;
	TestGraph();
	TestUndUnwGraphs();
	TestDUnwGraphs();
	TestUndWGraph();
	TestDWGraph();
}
