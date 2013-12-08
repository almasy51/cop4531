all: Dijkstra

Dijkstra.o: Dijkstra.cpp
	g++ -c Dijkstra.cpp -o Dijkstra.o

Dijkstra: Dijkstra.o
	g++ Dijkstra.o -o Dijkstra

clean:
	rm -f *o Dijkstra
	rm -f Dijkstra
