#pragma once
#ifndef NODE_H
#define NODE_H

#include <string.h>
#include <list>

using namespace std;

template <class T>
class Node
{

private: 
	Node* parent;
	Node* spawnparent;
	Node* rightchild;
	Node* leftchild;
	int height;
	int score;
	T data;
	// A Star Specific Variable
	bool open;

public:

	Node()
	{
	parent = NULL;
	spawnparent = NULL;
	leftchild = NULL;
	rightchild = NULL;
	height = 1;
	//ASTAR
	open = true;
	score = 0;
	}

	Node(T d)
	{
	parent = NULL;
	spawnparent = NULL;
	rightchild = NULL;
	leftchild = NULL;
	data = d;
	height = 1;
	//ASTAR
	open = true;
	score = 0;
	}

	Node(Node *n, T d)
	{
	parent = n;
	spawnparent = NULL;
	rightchild = NULL;
	leftchild = NULL;
	data = d;
	height = 1;
	
	//ASTAR
	open = true;
	score = 0;
	}

	bool operator <(Node &rhs)
	{
		if (score < rhs.getScore())
			return true;
		 else 
			 return false; 
	}

	Node* getParent(){ return parent; }
	Node* getLeftC() {return leftchild; }
	Node* getRightC() {return rightchild; }
	Node* getSpawnParent() {return spawnparent;}

	bool isOpen() {return open;}
	void close() { open = false; }
	void opened() { open = true; }

	void setLeftC(Node* c) {leftchild = c;}
	void setRightC(Node* c) {rightchild = c;}
	void setParent(Node *p){ parent = p; }
	void setSpawnParent(Node *n) {spawnparent = n;}
	
	int &H() { return height; }

	void setScore(int x) {score = x;}
	int& getScore() { return score; }

	void setData(T d){data = d;}
	T getData() { return data; }
	
	
	
};
#endif