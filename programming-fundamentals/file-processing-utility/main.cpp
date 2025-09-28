#include <iostream>
#include <vector>
#include<string>
#include<stdio.h>
#include <fstream>
using namespace std;

class Network
{
struct Computer{
int id;
Computer * next;
//method to enable if(n[i][j]) cout<<"i and j are connected.";
bool operator [] (int j)
    {
        if(id == j)
        {
            return true;
        }
        Computer* check = next;
        
        while(true)
        {
            if (check->id == j)
            {
                return true;
            }
            check = check->next;
            if (check == NULL)
            {
                return false;
            }
        }
    }
};
vector<Computer*> net; //built-in dynamic array
//add id into the list pointed to by head
void addConnection(Computer*&head, int id)
    {
        Computer* temp = head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
          
        }
        temp = new Computer;
        temp->next->id = id;
        temp->next->next=NULL;
    }

public:
//for empty network
Network()
    {
        net.clear();
    }

//read a network from a file
Network(string filename)
    {
        string network;
        ifstream net_file;
        net_file.open(filename);
        net_file.ignore();

        for(int i = 0; i < net.size(); i++)
        {
            getline(net_file,network);
            net[i]->id = network[0];
            Computer* head = new Computer;
            Computer* temp = new Computer;
            net[i] = head;
            net[i]->next = temp;
            for (int k = 4; k < network.length(); k++)
            {
                k = k+2;
            temp->id = network[k];
            temp = temp->next;
            }
        }
        net_file.close();
    }

//deep copy methods
Network(const Network& obj)
    {
        net = obj.net;
    }
const Network& operator =(const Network& obj)
    {
        net = obj.net;
        
            for (int i = 0; i < net.size(); i++)
            {
                net[i] = NULL;
        
                for (Computer* j = obj.net[i]; j != NULL; j = j->next)
                {
                    addConnection(net[i], j->id);
                }
            }

        return *this;
        
    }
//create net array of size, with no connections
Network(int size)
    {
        int x = 0;
        for (int i=0; i < size; i++)
        {
            net[i]->id = x;
            x++;
            net[i]->next = NULL;
        }
    }

//connect computers x and y
//use the utility method addConnection
void addConnection(int x, int y)
    {
            if (x < net.size() && y < net.size() && x != y && x > -1 && y > -1)
            {
                if (!(*net[x])[y])
                    addConnection(net[x], y);
        
                if (!(*net[y])[x])
                    addConnection(net[y], x);
            }

    }

//merge two networks (take union)
//computers, connections in any one of the networks appear in result
Network operator + (const Network& obj)
    {
        Network union1;
        
            if (net.size() >= obj.net.size())
            {
                union1 = *this;
        
                for (int i = 0; i < obj.net.size(); i++)
                {
                    Computer* k= new Computer;
                    for (k = obj.net[i]; k != NULL; k = k->next)
                    {
                        if (!((*net[i])[k->id]))
                            addConnection(union1.net[i], k->id);
                    }
                }
            }
        
            else
            {
                union1 = obj;
        
                for (int i = 0; i < net.size(); i++)
                {
                    Computer* k= new Computer;
                    for (k = net[i]; k != NULL; k = k->next)
                    {
                        if (!((*obj.net[i])[k->id]))
                            addConnection(union1.net[i], k->id);
                    }
                }
            }
        
            return union1;
    }

//intersect two networks (extract the common core)
//links and computers present in both networks appear in the result
Network operator * (const Network& obj)
    {
            int s = net.size();
        
            if (obj.net.size() < net.size())
                s = obj.net.size();
        
            Network intersect(s);
        
            for (int i = 0; i < s; i++)
            {
                for (Computer* k = net[i]; k != NULL; k = k->next)
                {
                    if ((*obj.net[i])[k->id])
                    {
                        addConnection(intersect.net[i], k->id);
                    }
                }
            }
        
            return intersect;
    }

//Remove the common connections of obj and this network
Network operator - (const Network& obj);

//Take complement of the Network
//Returns a network with the same computers
//but which contains complementary connections
//resultant contains connections which are absent in this network
Network operator - ();

//print the network
friend ostream & operator << (ostream & out, Network & obj)
    {
        for (int i = 0; i < obj.net.size(); i++)
            {
                out << i << ": ";
        
                Computer* temp = obj.net[i];
        
                while (temp != NULL)
                {
                    out << temp->id << " ";
                    temp = temp->next;
                }
        
                out << endl;
            }
            out << endl;
        
            return out;
    }

//method to enable if(n[i][j]){cout<<"i and j are connected.";}
Computer & operator [] (int i)
    {
        return *net[i];
    }

//add another computer to the network
Network operator ++ (int)
    {
        Network temp2 = *this;
        Computer* temp = new Computer;
        temp = NULL;
        net.push_back(temp);
        return temp2;
    }




//logical methods
//subNetwork returns true if obj is a sub-network of this network
bool subNetwork(const Network& obj)
    {
        bool a = false;
            if (obj.net.size() > net.size())
                return a;
        
            for (int i = 0; i < obj.net.size(); i++)
            {
                for (Computer* k = obj.net[i]; k != NULL; k = k->next)
                {
                    if (!(*net[i])[k->id])
                        return a;
                }
            }
            return !a;

    }

//get all neighbors of computer nid
vector<int> getNeighbors(int nid)
    {
        vector<int> neighbour;
        
            if (nid < net.size())
            {
                Computer* i = new Computer;
                for (i = net[nid]; i != NULL; i = i->next)
                {
                    neighbour.push_back(i->id);
                }
            }
        
            return neighbour;
    }

//get all unique neighbors-of-neighbors of computer nid
vector<int> getNeighborsOfNeighbors(int nid)
    {
        vector<int>neighbour;
        
            if (nid < net.size())
            {
                Computer* i = new Computer;
                for (i = net[nid]; i != NULL; i = i->next)
                {
                    vector<int> x = (*this).getNeighbors(i->id);
        
                    for (int j = 0; j < x.size(); j++)
                    {
                        if (x[j] != nid)
                        {
                            int m = 0;
                            for (; m < neighbour.size() && neighbour[m] != x[j]; m++);
                            if (m == neighbour.size())
                                neighbour.push_back(x[j]);
                        }
                    }
                }
            }
        
            return neighbour;
    }

//de-allocate network
~Network()
    {
        net.clear();
    }
};

int main()
{
        Network x;
        string name = "test1.txt";
        Network y(name);
        cout << "network y" << endl;
        cout << y;
    
        x = y;
        cout << "network x" << endl;
        cout << x;
    
        Network z = x + y;
        cout << "network z" << endl;
        cout << z;
    
        Network a = x * y;
        cout << "network a" << endl;
        cout << a;
    
    return 0;
}


/*
Vector usage and some important functions:

//Vector declaration: Creates a Vector of type int
vector<int> g1;

//Insert an element at the end of the vector
g1.push_back(5);
g1.push_back(123);

//Delete the last element in the vector, Basically the last element you inserted.
g1.pop_back();

//Get the size od vector i.e. the number of elements in the vector
int size = g1.size();

//Accessing the element at index i just like you do in an array
cout << g1[0];

//Accessing the first element of the vector
cout << g1.front();

//Accessing the last element of the vector
cout << g1.back();
*/
