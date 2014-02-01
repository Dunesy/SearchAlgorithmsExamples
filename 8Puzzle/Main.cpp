#include <list>
#include <vector>
#include <iostream>
#include<time.h>
#include "EightPuzzle.h"	
#include "EightPuzzleProblem.h"
								
								//123
using namespace std;			//804
								//765

int main (void)
{
	char c = NULL;
	int numstring = 0;
	srand(time(NULL));
	int num[9];
	//Node<EightPuzzle> * m;

	EightPuzzle x(1,2,3,4,5,6,7,8,0);
	EightPuzzleProblem z;
	//int x;
	
	Node<EightPuzzle> * m;

	
	while (c != 'y')
	{
		cout << "Enter a correct Num String for the Program to find a solution...\n(Leave it Blank if you want it Random)" << endl;
		cin >> numstring;
		
		if (numstring == 0)
		{
			m = new Node<EightPuzzle>(EightPuzzle());
		}else{
			for (int i = 8 ; i >= 0; i--)
			{
				num[i] = numstring % 10;
				numstring /= 10;
			}
			m = new Node<EightPuzzle>(EightPuzzle(num));
		}
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




