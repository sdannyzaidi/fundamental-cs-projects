#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here.
//
Graph::Graph(string file)
{
	// TODO
	ifstream myFile(file);
	char vertex1;
	char vertex2;
	string weight;
	string command;
	string size;

	while((myFile >> command >> size) && (command != "c"))
	{
		stringstream intSize(size);
		int newSize = 0;
		intSize >> newSize;
		this->size = newSize;
	}
	graph.assign(this->size, vector<int>(this->size,0));
	while(myFile >> vertex1 >> vertex2 >> weight)
	{
		stringstream intSize(weight);
		int weight = 0;
		intSize >> weight;
		addEdge(vertex1,vertex2,weight);
	}
	myFile.close();
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
//
void Graph::addEdge(char start, char end, int weight)
{
	int origin = convertChar(start);
	int dest = convertChar(end);
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			graph[origin][dest] = weight;
			graph[dest][origin] = weight;
		}
	}
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in manual.
//
string Graph::display()
{
	string displaystr;
	int weight = 0;
	string s,vertex1, vertex2;;
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			if (graph[i][j] == 0)
			{
				continue;
			}
			else
			{
				weight = graph[i][j];
				s = to_string(weight);
				vertex1 = convertInt(i);
				vertex2 = convertInt(j);
				displaystr +=  "(" + vertex1 + "," + vertex2 + "," + s + ")\n";
			}
			
		}
	}
	return displaystr;
}

string Graph::convertInt(int num)
{
	num = num +65;
	char c = static_cast<char>(num);
	string s(1,c);
	return s;
}

int Graph::convertChar(char start)
{
	int num = start-65;
	return num;
}

bool Graph::Reachable(char start, char end)
{
	/* reachability test using the BFS.
	*/
	int origin = convertChar(start);
	int dest = convertChar(end);
	/* This boolean array let us know that wether a vertex has been searched or not
	it acts in the same way as a set about which sir taught us. This array is first
	initalized to zero sice no vertex has been visited yet. Once a vertex is visited
	we mark that vertex index in the array to be true */

	bool marked[size];       
	for (int i=0; i<size; i++)
	{
		marked[i] = false;
	}

	queue<int> q1;
	/* Here we mark the start to be true since it is our first node and then put it in
	the queue. The while loop ahead runs untill all the nodes have been visited and the
	queue is empty. We pop each visited node the check wether it has a connection with
	an other, if it has a connection and that node has not already been visited than we 
	push it in the queue and then repeat the same procedure for all the nodes in a graph.*/

	marked[origin] = true;
	q1.push(origin);

	while(!q1.empty())
	{
		int check = q1.front();
		q1.pop();

		for(int j=0; j<size; j++)
		{
			if (graph[check][j]!=0)
			{
				if(marked[j] == false)
				{
					marked[j] = true;
					q1.push(j);
				}
			}
		}
	}
	return marked[dest];
}

//
// OPTION 2
// Returns the weight of the MST using Prims algorithm
//
int Graph::Prims()
{
	int infinity = pow(10,7);
	int ptr;
	int sum = 0;

	int sumarr[size]; // This sum array stores the weight of the least cost path
					  // from the source node to its neighbours.

	/* This boolean array let us know that wether a vertex has been searched or not
	it acts in the same way as a set about which sir taught us. This array is first
	initalized to zero sice no vertex has been visited yet. Once a vertex is visited
	we mark that vertex index in the array to be true */

	bool marked[size];
	for (int i=0; i<size; i++)
	{
		marked[i] = false;
		sumarr[i] = 0;
	}
	/*This weights array keeps the record of the weights of all the verticies connected
	to a node. At first we initialize all the weights to infinity, since right now the 
	node has no knowlegde of its neighbour weights. Start node is set to zero. Now since 
	no node is in marked start will be selected first since it has a weight of zero. Now
	start node onwards our algorithm will run until all the nodes are in the graph have 
	been visited and are in our marked array. Once a node is added to marked we will
	traverse through it adjacent nodes and see which adjacent node has the least weight.
	Once we find the adjacent node with the least weight we update the weight and then
	choose this new node as our source node and then look for its adjacent nodes with
	the least weight. This process is repeated until all the nodes are visited and
	a MST is formed. This case will only pass if the graph is connected.*/

	int arrWeights[size];
	for (int i=0; i<size; i++)
	{
		arrWeights[i] = infinity;
	}
	arrWeights[0] = 0; // First node is always set to zero, so that it is picked first

	for (int i=0; i<size; i++)
	{
		int findLeast = infinity;
		for (int j=0; j<size; j++)
		{
			if(arrWeights[j] <= findLeast && marked[j] == false) // finding path of least weight from all 
																 // adjacent neighbours
			{
				ptr = j;
				findLeast = arrWeights[j];
			}
		}
		marked[ptr] = true;
		for (int k=0; k<size; k++)
		{
			if(marked[k] == false) // if the node has already been explored, no need to update weights again
			{
				if(graph[k][ptr] != 0 && arrWeights[k] > graph[k][ptr])
				{
					arrWeights[k] = graph[k][ptr];
					sumarr[k] = graph[k][ptr];
				}
			}
			else
			{
				continue;
			}	
		}
	}
	
	for (int i=0; i<size; i++)
	{
		sum += sumarr[i];
	}
	return sum;
}

//
// OPTION 1
// Returns the weight of the MST using Kruskal algorithm
//
int Graph::Kruskal()
{
	// TODO
	return 0;
}

//
// Returns the weight of shortest path between start and end.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char end)
{
	int origin = convertChar(start);
	int dest = convertChar(end);
	int infinity = pow(10,7);
	int ptr;

	/* This boolean array let us know that wether a vertex has been searched or not
	it acts in the same way as a set about which sir taught us. This array is first
	initalized to zero sice no vertex has been visited yet. Once a vertex is visited
	we mark that vertex index in the array to be true */

	bool marked[size];
	for (int i=0; i<size; i++)
	{
		marked[i] = false;
	}
	/*This weights array keeps the record of the weights of all the verticies connected
	to a node. At first we initialize all the weights to infinity, since right now the 
	node has no knowlegde of its neighbour weights. Start node is set to zero. Now since 
	no node is in marked start will be selected first since it has a weight of zero. Now
	start node onwards our algorithm will run until all the nodes are in the graph have 
	been visited and are in our marked array. Once a node is added to marked we will
	update the weights of all the neighbours of that node. We update the only in that 
	condition when the weight of a node is less than the sum of weight from the sourec
	and the weight of the edge.*/

	int arrWeights[size];
	for (int i=0; i<size; i++)
	{
		arrWeights[i] = infinity;
	}
	arrWeights[origin] = 0;

	for (int i=0; i<size; i++)
	{
		int findLeast = infinity;
		for (int j=0; j<size; j++)
		{
			if(arrWeights[j] <= findLeast && marked[j] == false) // finding paths with least weight
			{
				ptr = j;
				findLeast = arrWeights[j];
			}
		}
		marked[ptr] = true;
		for (int k=0; k<size; k++)
		{
			if(marked[k] == false) // if the node has already been explored, no need to update weights again
			{
				int compWeight = graph[ptr][k]+arrWeights[ptr];
				if(graph[k][ptr] != 0 && arrWeights[k] > compWeight)
				{
					arrWeights[k] = arrWeights[ptr] + graph[k][ptr]; //updating the weights
				}
			}
			else
			{
				continue;
			}	
		}
	}
	if (arrWeights[dest] == infinity)
	{
		return -1; //returning -1 if no connection between nodes
	}

	return arrWeights[dest];
}

#endif
