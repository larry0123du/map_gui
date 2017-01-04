all: lab6

lab6: plot.cpp Graph.cpp faster_dijkstra.cpp Astar.cpp IDA_star.cpp Graph.h Astar.h plot.h
	g++ -std=c++11 -o lab6 plot.cpp Graph.cpp faster_dijkstra.cpp Astar.cpp IDA_star.cpp -lglut -lGLU -lGL

clean:
	rm -rf lab6
