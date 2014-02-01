#include <list>
#include <vector>
#include <iostream>
#include<time.h>
#include "transpo_state.h"
#include "TransportProblem.h"	
										
using namespace std;			
								

int main (void)
{
	char c = NULL;
	int numstring = 0;
	srand(time(NULL));
	int num[9];
	Node<Transpo_State> *m ;
	TransportProblem z;

	while (c != 'y')
	{
		cout << "Enter a Number n for the number of Tigers, Hay and Goats to transport" << endl;
		cin >> numstring;
		
		m = new Node<Transpo_State>(Transpo_State(numstring));
		
		//Choose The Search Pattern

		cout << "Choose Search: (a)BreadthFirstSearch (b)DepthFirstSearch (c)AStarSearch" << endl;
		cin >> c;

		if (c == 'a')
			z.BreadthFirstSearch(m);
		else if (c == 'b')
			z.DepthFirstSearch(m);
		else if (c == 'c')
			z.AStarSearch(m);

		cout << "Quit?(y/n)" << endl;
		cin >> c;

	}

	return 0;
}




