#include <iostream>
#include "avl.hpp"
#include "zambeel.hpp"
#include <stack>
#include<cstdlib>
#include<ctime>
#include<chrono>
using namespace std;
using namespace std::chrono;

Zambeel::Zambeel(bool isAVL) {

	myTree = new AVL<int,int>(isAVL);
}

Zambeel::~Zambeel() {

	delete myTree;
}

bool Zambeel::istAddCourse(int course_id) {
	node<int,int> *currNode = new node<int,int>(course_id,0);
	currNode->key = course_id;
	myTree->insertNode(currNode);
	return true;
}

bool Zambeel::istDropCourse(int course_id) {
	myTree->deleteNode(course_id);
	return true;
}

void Zambeel::istCleanEnrollment() {
	stack<node<int,int>*> cleanStack;
	node<int,int> *currNode = myTree->getRoot();
	cleanStack.push(currNode);
	while(!(cleanStack.empty()))
	{
		currNode = cleanStack.top();
		cleanStack.pop();
		currNode->value = 0;
	}
	return;
}


bool Zambeel::stuAddCourse(int course_id) {
	node<int,int> *currNode = myTree->searchNode(course_id);
	if (currNode == NULL)
	{
		return false;
	}
	else
	{
		currNode->value = currNode->value + 1;
	}
	return true;
}

bool Zambeel::stuDropCourse(int course_id) {
node<int,int> *currNode = myTree->searchNode(course_id);
	if (currNode == NULL)
	{
		return false;
	}
	else
	{
		currNode->value = currNode->value - 1;
	}
	return true;
}

bool Zambeel::stuSwapCourse(int course1_id, int course2_id) {
	node<int,int> *swapWith = myTree->searchNode(course1_id);
	node<int,int> *toSwap = myTree->searchNode(course2_id);
	if(toSwap ==NULL || swapWith == NULL)
	{
		return false;
	}
	else if (toSwap->value == 0)
	{
		return false;
	}
	else
	{
		swapWith->value = swapWith->value + 1;
		toSwap->value = toSwap->value - 1;
	}
	return true;
}


int main()
{
	Zambeel zAVL(1);
	Zambeel zBST(0);
	for (int i = 1; i<=10; i++)
	{
		zAVL.istAddCourse(i);
		zBST.istAddCourse(i);
	}
	srand(time(0));
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		int num1 = rand() % 3 + 1;
		int num2 = rand() % 100 + 1;
		if (num1 == 1)
		{
			zAVL.stuAddCourse(num2);
		} 
		else if (num1 == 2)
		{
			zAVL.stuDropCourse(num2);
		}
		else if (num1 == 3)
		{
			zAVL.stuSwapCourse(num2,num1);
		}
	} 
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start); 
	cout << "Ascending Order in AVL " << duration.count() <<" nanoseconds" <<endl;
	
	start = high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		int num1 = rand() % 3 + 1;
		int num2 = rand() % 100 + 1;
		if (num1 == 1)
		{
			zBST.stuAddCourse(num2);
		} 
		else if (num1 == 2)
		{
			zBST.stuDropCourse(num2);
		}
		else if (num1 == 3)
		{
			zBST.stuSwapCourse(num2,num1);
		}
	} 
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start); 
	cout << "Ascending Order in BST " << duration.count() << " nanoseconds" << endl;

	zAVL.istCleanEnrollment();
	zBST.istCleanEnrollment();
	int arrLR [] = {200,150,250,144,177,202,252,130,148,160};
	for (int i = 0; i < 10; i++)
	{
		zAVL.istAddCourse(arrLR[i]);
		zBST.istAddCourse(arrLR[i]);
	}
	start = high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		int num1 = rand() % 3 + 1;
		int num2 = rand() % 100 + 1;
		if (num1 == 1)
		{
			zAVL.stuAddCourse(num2);
		} 
		else if (num1 == 2)
		{
			zAVL.stuDropCourse(num2);
		}
		else if (num1 == 3)
		{
			zAVL.stuSwapCourse(num2,num1);
		}
	} 
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start); 
	cout << "Left to Right Order in AVL " << duration.count() << " nanoseconds" << endl;

	start = high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		int num1 = rand() % 3 + 1;
		int num2 = rand() % 100 + 1;
		if (num1 == 1)
		{
			zBST.stuAddCourse(num2);
		} 
		else if (num1 == 2)
		{
			zBST.stuDropCourse(num2);
		}
		else if (num1 == 3)
		{
			zBST.stuSwapCourse(num2,num1);
		}
	} 
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start); 
	cout << "Left to Right Order in BST " << duration.count() << " nanoseconds" << endl;

	zAVL.istCleanEnrollment();
	zBST.istCleanEnrollment();
	int arrRand [10] = {};
	for (int i = 0; i <10; i++)
	{
		arrRand[i] = rand() % 100 + 1;
	}
	for (int i = 0; i < 10; i++)
	{
		zAVL.istAddCourse(arrRand[i]);
		zBST.istAddCourse(arrRand[i]);
	}

	start = high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		int num1 = rand() % 3 + 1;
		int num2 = rand() % 100 + 1;
		if (num1 == 1)
		{
			zAVL.stuAddCourse(num2);
		} 
		else if (num1 == 2)
		{
			zAVL.stuDropCourse(num2);
		}
		else if (num1 == 3)
		{
			zAVL.stuSwapCourse(num2,num1);
		}
	} 
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start); 
	cout << "Random Order in AVL " << duration.count() << " nanoseconds" << endl;

	start = high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		int num1 = rand() % 3 + 1;
		int num2 = rand() % 100 + 1;
		if (num1 == 1)
		{
			zBST.stuAddCourse(num2);
		} 
		else if (num1 == 2)
		{
			zBST.stuDropCourse(num2);
		}
		else if (num1 == 3)
		{
			zBST.stuSwapCourse(num2,num1);
		}
	}
	stop = high_resolution_clock::now();
	duration = duration_cast<nanoseconds>(stop - start); 
	cout << "Random Order in BST " << duration.count() << " nanoseconds" << endl;


	return 0;
}