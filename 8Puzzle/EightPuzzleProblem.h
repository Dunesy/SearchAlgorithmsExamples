
#include <list>
#include <vector>
#include <algorithm>
#include "Node.h"
#include "NodeController.h"
#include "EightPuzzle.h"
#include <fstream>


using namespace std;

//Heap Methods
void min_heapify(vector<Node<EightPuzzle>*> &heap, int i);
void build_heap(vector<Node<EightPuzzle>*> &heap);
void min_heap_insert(vector<Node<EightPuzzle>*> &heap, Node<EightPuzzle>* key);
Node<EightPuzzle>* extract_min(vector<Node<EightPuzzle>*> &heap);
void heap_increase_key(vector<Node<EightPuzzle>*> &heap, int i, Node<EightPuzzle>* key);

int Parent(int x);
int Left(int x);
int Right(int x);

class EightPuzzleProblem
{

private:

NodeController<EightPuzzle> nc;
list<Node<EightPuzzle>*> allnodes;

public:

//Method Prototypes
void inordertrav(Node<EightPuzzle> *n);
void spawnNodes(Node<EightPuzzle> *n, list<Node<EightPuzzle>*>& addon);
void starspawnNodes(Node<EightPuzzle> *n, list<Node<EightPuzzle>*>& addon);
vector<Node<EightPuzzle>*> tracepath( Node<EightPuzzle> *n );
void printPath(vector<Node<EightPuzzle>*> path);

void BreadthFirstSearch(Node<EightPuzzle> *n);
void DepthFirstSearch(Node<EightPuzzle> *n);
void AStarSearch(Node<EightPuzzle> * n);




};


void EightPuzzleProblem::spawnNodes(Node<EightPuzzle> *n, list<Node<EightPuzzle>*>& addon)
{		
	list<EightPuzzle> states;
	//Generate States
	n->getData().generateStates(states);
	// Checks For Duplicates of the potential nodes;
	for (list<EightPuzzle>::iterator it = states.begin(); it != states.end(); ++it)
	{
			Node<EightPuzzle> *m;
			if (nc.insert(*it, nc.getRoot(), m))
			{
				m->setSpawnParent(n);
				addon.push_back(m);
			}
			// Adds the non matching states to a temp vector
			//constructed++;
		
	}	
}


void EightPuzzleProblem::BreadthFirstSearch(Node<EightPuzzle> *n)
{
	list<Node<EightPuzzle>*> nodelist;
	vector<Node<EightPuzzle>*> path;
	bool goalstate = false;
	int counter = 0 ;
	//Add First Node into the list
	nc.setRoot(n);
	nodelist.push_back(n);
	allnodes.push_back(n);
	//Iterator
	while (!goalstate && !nodelist.empty()) //While Goal State is Not Found And The Node List is not Empty Continue
	{
	  //cout << "Num Created: " << nodelist.size() << endl;
	  list<Node<EightPuzzle>*> addon;
	  spawnNodes(nodelist.front(), addon);
	  counter += addon.size();
	 
	  for( list<Node<EightPuzzle>*>::iterator it2 = addon.begin(); it2 != addon.end(); ++it2 )
	  { 
		  nodelist.push_back(*it2);
		  allnodes.push_back(*it2);
		  if ( (*it2)->getData().goalstate())
		 {
			path = tracepath(*it2);
			goalstate = true;
		 }
	  }
	  nodelist.pop_front();
	}

	cout << "Goal State Found..." << endl;
	cout << "Nodes Explored: " << counter << endl;
	printPath( path );
	cout << "Solution Output Created" << endl;

	while (!allnodes.empty())
	{
		delete allnodes.front();
		allnodes.pop_front();
	}


}	


void EightPuzzleProblem::DepthFirstSearch(Node<EightPuzzle> *n)
{
	list<Node<EightPuzzle>*> nodelist;
	vector<Node<EightPuzzle> *> path;
	bool goalstate = false;
	int counter = 0 ;
	//Add First Node into the list
	nodelist.push_back(n);
	allnodes.push_back(n);
	nc.setRoot(n);
	//Iterator
	while (!goalstate && !nodelist.empty()) //While Goal State is Not Found And The Node List is not Empty Continue
	{
	  //cout << "Num Created: " << constructed << endl;
	  list<Node<EightPuzzle>*> addon;
	  spawnNodes(nodelist.back(), addon);
	  counter += addon.size();
	  nodelist.pop_back();
	  for( list<Node<EightPuzzle>*>::iterator it = addon.begin(); it != addon.end(); ++it ) 
	  {
		  nodelist.push_back(*it);
		  allnodes.push_back(*it);
		  if ((*it)->getData().goalstate())
		  {
			  goalstate = true;
			  path = tracepath(*it);
		  }
	}
	  
	}

	cout << "Goal State Found..." << endl;
	cout << "Nodes Explored: " << counter << endl;
	printPath( path );
	cout << "Solution Output Created" << endl;
	while (!allnodes.empty())
	{
		delete allnodes.front();
		allnodes.pop_front();
	}


}

//Heuristic Specific Generator of States
void EightPuzzleProblem::starspawnNodes(Node<EightPuzzle> *n, list<Node<EightPuzzle>*>& addon)
{		
	list<EightPuzzle> states;
	//Generate States
	n->getData().generateStates(states);
	
	// Checks For Duplicates of the potential nodes;
	for (list<EightPuzzle>::iterator it = states.begin(); it != states.end(); ++it)
	{
			Node<EightPuzzle> *m;
			(*it).setDepth(n->getData().getDepth() + 3);
			(*it).updateScore();
			if (nc.insert(*it, nc.getRoot(), m)) //If Duplicate Does Not Exist Add to the queue
			{
				m->setSpawnParent(n);
				addon.push_back(m);
				allnodes.push_back(m);
			}
			else
			{ //If it does, Compare the score of the existing state with the new one
				Node<EightPuzzle> *m = nc.search(*it);
				if (m->getData().getScore() > (*it).getScore() && m->isOpen()) //If state is in nodelist update that node with the better score and parent
				{																		
					m->getData().setDepth((*it).getDepth());
					m->getData().updateScore();
					m->setScore(m->getData().getScore());
					m->setSpawnParent(n);
				}
				else if ( m->getData().getScore() > (*it).getScore() && !m->isOpen() ) //If State is not in nodelist Add that node to the list once again.
				{
					m->getData().setDepth((*it).getDepth());
					m->getData().updateScore();
					m->setScore(m->getData().getScore());
					m->opened();
					m->setSpawnParent(n);
					addon.push_back(m);					
				}

			}
		
	}	
}

void EightPuzzleProblem::AStarSearch(Node<EightPuzzle> *n)
{
	vector<Node<EightPuzzle>*> path;
	vector<Node<EightPuzzle>*> nodelist;
	nodelist.reserve( 370000 );
	bool goalstate = false;
	int counter = 0 ;
	//Add First Node into the list
	n->setScore(n->getData().getScore());
	nodelist.push_back(n);
	nodelist.push_back(n);
	allnodes.push_back(n);
	nc.setRoot(n);

	int size = 0;
	
	//Iterator
	build_heap(nodelist);

	while (!goalstate && !nodelist.empty()) //While Goal State is Not Found And The Node List is not Empty Continue
	{
	  list<Node<EightPuzzle>*>addon;
	  
	  nodelist[1]->close();
	
	  if (nodelist[1]->getData().goalstate())
	  { 
		  goalstate = true;
		  path = tracepath (nodelist[1]);
	  }
	  
	  starspawnNodes(extract_min(nodelist) , addon);
	  
	  counter += addon.size();
	  size = nodelist.size();
	  
	  for( list<Node<EightPuzzle>*>::iterator it2 = addon.begin(); it2 != addon.end(); ++it2 )
	  { 
		  min_heap_insert(nodelist, *it2);
	  }
		 
	}

	cout << "Goal State Found..." << endl;
	cout << "Nodes Explored: " << counter << endl;
	printPath( path );
	cout << "Solution Output Created" << endl;

	while (!allnodes.empty())
	{
		if (allnodes.front() != NULL)
		{
			delete allnodes.front();
			allnodes.front() = NULL;
		}
			allnodes.pop_front();
		
	}


}


vector<Node<EightPuzzle>*> EightPuzzleProblem::tracepath( Node<EightPuzzle> *n )
	{
		vector<Node<EightPuzzle>*> path;
		path.push_back(n);
		while (n->getSpawnParent() != NULL)
		{
			n = n->getSpawnParent();
			path.push_back(n);
			
		} 
		cout << "Path Size is... " << path.size() << endl;
		return path;
	}
void EightPuzzleProblem::printPath(vector<Node<EightPuzzle>*> path)
{
	ofstream myfile;
	myfile.open("8Puzzle Solution.txt");
	while (!path.empty())
	{
			string s = path.back()->getData().print();
			for (string::iterator it =s.begin() ; it < s.end(); it++)
			{
				myfile << *it;
			}
			path.pop_back();
	}
		 
	myfile.close();
}

int Parent(int x) { return x / 2 ; }
int Left(int x) { return 2 * x ; }
int Right(int x) { return 2 * x + 1; }

void min_heapify(vector<Node<EightPuzzle>*> &heap, int i)
{
	int l = Left(i);
	int r = Right(i);
	int smallest;
	if (l <= heap.size() - 1 && *(heap[l]) < *(heap[i]))
		smallest = l;
	else
		smallest = i;
	if (r <= heap.size() - 1 &&  *(heap[r]) < *(heap[smallest]))
		smallest = r;
	
	if (smallest != i)
	{
		Node<EightPuzzle>* temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		min_heapify(heap, smallest);
	}

	
}

void build_heap(vector<Node<EightPuzzle>*> &heap)
{
	int heap_size = heap.size();
	for (int i = (heap.size() - 1) / 2 ; i >= 1; i--)
	{
		min_heapify(heap, i);
	}
}

Node<EightPuzzle>* extract_min(vector<Node<EightPuzzle>*> &heap)
{
	Node<EightPuzzle> *n = heap[1];
	heap[1] = heap.back();
	heap.pop_back();
	if (heap.size() > 2)
		min_heapify(heap, 1);
	return n;
}

void heap_increase_key(vector<Node<EightPuzzle>*> &heap, int i, Node<EightPuzzle>* key)
{
	if (key > heap[i])
	{
		cout << "New Key is Smaller than current Key";
	}
	heap[i] = key;
	while (i > 1 && *(heap[i]) < *(heap[Parent(i)]) )
	{
		Node<EightPuzzle>* temp;
		
		temp = heap[i];
		heap[i] = heap[Parent(i)];
		heap[Parent(i)] = temp;
		
		i = Parent(i);
	}

}

void min_heap_insert(vector<Node<EightPuzzle>*> &heap, Node<EightPuzzle>* key)
{
	heap.push_back(key);
	heap_increase_key(heap,heap.size()-1,key);
}


