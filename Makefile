all: map

map: plot.cpp Graph.cpp faster_dijkstra.cpp Astar.cpp IDA_star.cpp Graph.h Astar.h plot.h
	g++ -std=c++1z -o map plot.cpp Graph.cpp faster_dijkstra.cpp Astar.cpp IDA_star.cpp -lglut -lGLU -lGL

clean:
	rm -rf map
