CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic

TARGET = zzz
OBJ = graph.o paths.o connected_components.o cycles.o topological_order.o \
prim_mst.o index_min_pq.o shortest_paths.o tests.o main.o

.PHONY: all clean  # prevent make from confusing the phony target with a file name

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

re: clean all

graph.o: graph.h graph.cpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

paths.o: graph.h paths.h paths.cpp
	$(CXX) $(CXXFLAGS) -c paths.cpp

connected_components.o: graph.h connected_components.h connected_components.cpp
	$(CXX) $(CXXFLAGS) -c connected_components.cpp

cycles.o: graph.h cycles.h cycles.cpp
	$(CXX) $(CXXFLAGS) -c cycles.cpp

topological_order.o: graph.h cycles.h topological_order.h topological_order.cpp
	$(CXX) $(CXXFLAGS) -c topological_order.cpp

prim_mst.o: graph.h prim_mst.h prim_mst.cpp
	$(CXX) $(CXXFLAGS) -c prim_mst.cpp

index_min_pq.o: index_min_pq.h index_min_pq.cpp
	$(CXX) $(CXXFLAGS) -c index_min_pq.cpp

shortest_paths.o: graph.h shortest_paths.h shortest_paths.cpp
	$(CXX) $(CXXFLAGS) -c shortest_paths.cpp

tests.o: graph.h paths.h connected_components.h cycles.h \
topological_order.h prim_mst.h shortest_paths.h tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)
