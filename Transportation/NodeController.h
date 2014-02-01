
#ifndef NODECONTROLLER_H
#define NODECONTROLLER_H

#include "Node.h"
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class NodeController
{
private:
	Node<T> *root;
	list<Node<T>*> allnodes;

public:
	//Constructor
	NodeController()
	{
		root = NULL;
	}
	
	NodeController(Node<T> *n)
	{
		root = n;
		allnodes.push_back(n);
	}
	
/////////////////////////////////
//////  AVL Tree Functions///////
/////////////////////////////////
Node<T> * getRoot() {return root;}
void setRoot(Node<T> *n) { root = n ; }


Node<T>* search(T &x) 
{
	Node<T> *n = root;
	while (n != NULL)
	{
		if (n->getData() == x)
			return n;
		else if (n->getData() > x)
			n = n->getLeftC();
		else if (n->getData() < x)
			n = n->getRightC();
	}
	return NULL;
}


bool insert(T &x, Node<T> *n, Node<T>* &m )
{
	bool searching = true;

	while (searching)
	{
		if (n->getData() == x)
			return false;
		else if (n->getData() < x && n->getRightC() != NULL)
			n = n->getRightC();
		else if(n->getData() > x && n->getLeftC() != NULL)
			n = n->getLeftC();
		else if (n->getData() < x && n->getRightC() == NULL)
		{
			searching = false;
			Node<T>* t;
			t = new Node<T>(x);	
			t->setParent(n);
			n->setRightC(t);
			t->setScore(x.getScore());
			m = t;
		}
		else
		{
			searching = false;
			Node<T>* t;
			t = new Node<T>(x);	
			t->setParent(n);
			n->setLeftC(t);
			t->setScore(x.getScore());
			m = t;
		}
	}

	
	while (n != NULL)
	{
		adjustHeight(n);
		if (!isBalanced(n))
		{
			rebalance(n);
			adjustHeight(n);	
		}
		else
		{
			n = n->getParent();
		}
	}
	
	
	return true;
}

void adjustHeight(Node<T> * n)
{
	if (n->getRightC() != NULL && n->getLeftC() != NULL)
			n->H() = 1 + max(n->getLeftC()->H(), n->getRightC()->H());
	else if (n->getRightC() == NULL && n->getLeftC() != NULL) 
		n->H() = 1 + n->getLeftC()->H();
	else if(n->getLeftC() == NULL && n->getRightC() != NULL)
		n->H() = 1 + n->getRightC()->H();
	else 
		n->H() = 1;
}

bool isBalanced(Node<T> *n)
{
	//Comparing Each Child's Height
	if (n->getLeftC() != NULL && (n->getRightC()) != NULL)
	{
		if ( abs( n->getLeftC()->H() - n->getRightC()->H()) > 1)
			return false;
	}
	else if (n->getLeftC() == NULL)
	{
		if (n->getRightC() != NULL && n->getRightC()->H() > 1)
			return false;
	}
	else if (n->getRightC() == NULL)
	{
		if (n->getLeftC() != NULL && n->getLeftC()->H() > 1)
			return false;
	}

	return true;
}

bool isRightHeavy(Node<T> * n)
{
	if (n->getLeftC() == NULL && n->getRightC() != NULL)
		return true;
	if (n->getLeftC() != NULL && n->getRightC() != NULL && n->getRightC()->H() > n->getLeftC()->H())
		return true;
	else
		return false;
}

bool isLeftHeavy(Node<T> * n)
{
	if (n->getRightC() == NULL && n->getLeftC() != NULL)
		return true;
	if (n->getRightC() != NULL && n->getLeftC() != NULL && n->getLeftC()->H() > n->getRightC()->H())
		return true;
	else
		return false;

}

int printInOrder(Node<T> *n)
{
	if (n == NULL)
	  return 0;

	int h = 1;
	
	h += printInOrder(n->getLeftC());
	n->getData().print();

	h += printInOrder(n->getRightC());

	return h;
	
}

void rebalance(Node<T>* n)
{
	if (isLeftHeavy(n))
	{
		if (n->getLeftC() != NULL && isLeftHeavy(n->getLeftC()))
			rightRotation(n);
		else
			doubleRight(n);
	}
	else
	{
		if (n->getRightC() != NULL && isRightHeavy(n->getRightC()))
			leftRotation(n);
		else
			doubleLeft(n);
	}
}

void rightRotation(Node<T> *n)
{
	//Perform Right Rotation
	Node<T> * y = n->getLeftC();
	Node<T> * z = y->getLeftC();
		
	//y's children must be handled
	if (y->getRightC() != NULL)
		y->getRightC()->setParent(n);
	n->setLeftC(y->getRightC());
	//n's Parent Must Be Handled
	if (n->getParent() != NULL)
		if (n->getParent()->getLeftC() == n)
			n->getParent()->setLeftC(y);
		else
			n->getParent()->setRightC(y);
	
	//Set y's Parent and Children
	y->setParent(n->getParent());
	y->setRightC(n);
	y->setLeftC(z);
	n->setParent(y);
	//Adjust the Heights of the Nodes
	adjustHeight(z);
	adjustHeight(n);
	adjustHeight(y);
	if (y->getParent() == NULL)
		root = y;
}

void leftRotation(Node<T> *n)
{
	//Perform Left Rotation
	Node<T> * y = n->getRightC();
	Node<T> * z = y->getRightC();
		
	//y's children must be handled
	if (y->getLeftC() != NULL)
		y->getLeftC()->setParent(n);
	n->setRightC(y->getLeftC());

	//n's Parent Must Be Handled
	if (n->getParent() != NULL)
		if (n->getParent()->getLeftC() == n)
			(n->getParent()->setLeftC(y));
		else
			(n->getParent()->setRightC(y));
	//Set y's Parent and Children
	y->setParent(n->getParent());
	y->setRightC(z);
	y->setLeftC(n);
	n->setParent(y);
	//Adjust The Heights of the Nodes
	adjustHeight(z);
	adjustHeight(n);
	adjustHeight(y);
	if (y->getParent() == NULL)
		root = y;
}

void doubleRight(Node<T> *n)
{
	//Perform Double Right
	Node<T> * y = n->getLeftC();
	Node<T> * z = y->getRightC();
	//z's children must be handled
	y->setRightC(z->getLeftC());
	n->setLeftC(z->getRightC());
	//z's children's parents
	if (z->getRightC() != NULL)
		z->getRightC()->setParent(n);
	if (z->getLeftC() != NULL)
		z->getLeftC()->setParent(y);
	//n's Parent Must Be Handled
	if (n->getParent() != NULL)
		if (n->getParent()->getLeftC() == n)
			n->getParent()->setLeftC(z);
		else
			n->getParent()->setRightC(z);
	//Set z's Parent and Children
	z->setParent(n->getParent());
	z->setRightC(n);
	z->setLeftC(y);
	//Set N and Y's Parents
	y->setParent(z);
	n->setParent(z);
	//Adjust heights
	adjustHeight(n);
	adjustHeight(y);
	adjustHeight(z);
	if (z->getParent() == NULL)
		root = z;
}

void doubleLeft(Node<T> *n)
{
	//Perform Double Right
	Node<T> *y = n->getRightC();
	Node<T> *z = y->getLeftC();
	//z's children must be handled
	y->setLeftC(z->getRightC());
	n->setRightC(z->getLeftC());
	//z's children's parents
	if (z->getRightC() != NULL)
		z->getRightC()->setParent(y);
	if (z->getLeftC() != NULL)
		z->getLeftC()->setParent(n);
	//n's Parent Must Be Handled
	if (n->getParent() != NULL)
		if (n->getParent()->getLeftC() == n)
			n->getParent()->setLeftC(z);
		else
			n->getParent()->setRightC(z);
	//Set z's Parent and Children
	z->setParent(n->getParent());
	z->setRightC(y);
	z->setLeftC(n);
	//Set N and Y's Parents
	y->setParent(z);
	n->setParent(z);
	//Adjust heights
	adjustHeight(n);
	adjustHeight(y);
	adjustHeight(z);
	if (z->getParent() == NULL)
		root = z;
}


};
#endif
