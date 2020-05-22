#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
#include <list>
#include <sstream>
#include <stack>
// You may include more libraries.
#include <cmath>


using namespace std;

class Edge
{
	// You may add more variables and functions in this class
public:
	char origin;
	char dest;
	int weight;
};

class Graph
{
	//
	// You are required to implement the data structures for the graph. Two representations
	// you will be familiar with are adjaceny list and adjacency matrix.
	// You can choose to go with any representation you wish.
	//

public:
	//
	// To get you started, we have written the definitions for both adjacency list
	// and matrix. You can uncomment whichever one you like. You are also free to change
	// the data structure to your liking. HOWEVER:
	// MAKE SURE YOU DO NOT CHANGE NAME FROM 'graph' OTHERWISE THE TESTS WILL FAIL.
	//
	// Matrix:
	vector<vector<int>> graph;//using int instead of Edge class, since its an overkill and more space consuming.
	//
	// List:
	// vector<list<Edge *>> graph;
	//
	int size = 0;
	Graph(string filename);

	void addEdge(char start, char end, int weight);
	string display(); // displays the graph
	bool Reachable(char start, char dest);
	int Prims();
	int Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree weight
	int Dijkstra(char start, char dest);
	//
	// Add any helper function definitions here...
	int convertChar(char start);
	string convertInt(int num);
	//
	// We encourage you to make a helper function that can easily translate a city name to its
	// index.
	// ...
	//
};

#endif
