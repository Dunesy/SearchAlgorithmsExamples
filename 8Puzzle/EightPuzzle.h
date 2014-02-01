#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H

#include<list>
#include <string>

using namespace std;

static enum Position { BLANK = 4 , ONE = 0 , TWO = 1 , THREE = 2 , FOUR = 5, FIVE = 8 , SIX = 7, SEVEN = 6, EIGHT = 3 };


class EightPuzzle
{

private:
	
	int x, y;
	int score;
	int score2;
	int state[9];
	int numstring;
	int depth;
	
public:
	
	EightPuzzle(int t11, int t12, int t13, int t21, int t22, int t23, int t31, int t32, int t33)
	{
		state[0] = t11;
		state[1] = t12;
		state[2] = t13;
		state[3] = t21;
		state[4] = t22;
		state[5] = t23;
		state[6] = t31;
		state[7] = t32;
		state[8] = t33;
		bool found = false;
		int i = 0;
		while (!found)
		{
			if (state[i] == 0)
				{
					x = i%3;
					y = i/3;
					found = true;	
				}
			i++;
		manhattandistance();
		depth = 0;
		numstring = toInteger();
		}
	}

	EightPuzzle( int num[])
	{
		for (int i = 0 ; i < 9; i++)
		{
			if (num[i] == 0)
			{
				x = i%3;
				y = i/3;
			}
			state[i] = num[i];
		}
		manhattandistance();
		depth = 0;
		numstring = toInteger();
	}

	//Constructors
	EightPuzzle()
	{
		int num[] = {0,1,2,3,4,5,6,7,8};
		int temp;
		//Number Swaps
		for (int i = 0 ; i < 100; i++)
		{
			int z = rand() % 9;
			temp = num[(i % 9)];
			num[(i % 9)] = num[z];
			num[z] = temp;
		}
		///
		for (int i = 0 ; i < 9 ; i++)
		{
			if (num[i] == 0)
			{
				x = i % 3;
				y = i / 3;
			}
			state[i] = num[i];
		}
		manhattandistance();
		numstring = toInteger();
		depth = 0;
	}
	
	EightPuzzle(int (&s)[9],int x1,int y1, int u, int v)
	{
		x = (u);
		y = (v);
		for (int i = 0 ; i < 9 ; i++)
			state[i] = s[i];
		
		swap2(x1, y1, u, v);
		manhattandistance();
		depth = 0;
		numstring = toInteger();
	}

	EightPuzzle(int (&s)[9], int u, int v)
	{
		x = u;
		y = v;
		for (int i = 0 ; i < 9 ; i++)
			state[i] = s[i];
		manhattandistance();
		depth = 0;
	}

	//Comparison Overlaods
	 bool operator ==(EightPuzzle &rhs) 
	 {
		if (numstring == rhs.getIntString())
			return true;
		else
			return false;
	 }

	 bool operator >(EightPuzzle &rhs)
	 {
		 if (numstring > rhs.getIntString())
			return true;
		 else 
			 return false; 
	 }
	 
	 bool operator <(EightPuzzle &rhs)
	 {
		if (numstring < rhs.getIntString())
			return true;
		 else 
			 return false; 
	 }


 
	///////Output Functions //////////
	string print()
	{
		char str[15];
		sprintf_s(str, "%d%d%d\n%d%d%d\n%d%d%d\n\n", state[0],state[1],state[2],state[3],state[4],state[5],state[6],state[7],state[8]);
		string s(str);
		return s;
	}

	

	int toInteger() 
	{
		int c = 1;
		int num = 0;
		for (int i = 8; i >= 0; i--)
		{
			num += state[i] * c;	
			c *= 10;
		}
		return num;
	}
	int &getIntString() {return numstring;}
	bool goalstate() { return (numstring == 123804765); }
	
	/////////////////////////////////

	bool swap(int x1 , int y1, int x2, int y2)
	{
		if (x2 < 3 && x2 >= 0 && y2 < 3 && y2 >= 0 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void  swap2(int x1, int y1, int x2, int y2)
	{
		int temp = state[y1*3 + x1];
		state[y1*3 + x1] = state[y2*3 + x2];
		state[y2*3 + x2] = temp;
		numstring = toInteger();
		manhattandistance();
	}

	bool swap3(int x1, int y1, int x2, int y2)
	{
		if (state[(x1 + 3 * y1)] != 0 && state[(x2 + 3 * y2)] != 0)
			return true;
		else return false;
	}

	int getScore() { return score; }
	
	///////////////A* Heuristic Search ///////////////
	//////Manhattan Distance////////
	void manhattandistance()
	{
		score = 0;
		for (int i = 0 ; i < 9 ; i++)
		{
			if (state[i] == 1){	score += abs(i/3 - ONE/3)  + abs(i%3 - ONE%3); }
			
			else if (state[i] == 2){	score += abs(i/3 - TWO/3)  + abs(i%3 - TWO%3); }
		
			else if (state[i] == 3){	score += abs(i/3 - THREE/3)  + abs(i%3 - THREE%3); }
			
			else if (state[i] == 4){	score += abs(i/3 - FOUR/3)  + abs(i%3 - FOUR%3); }
			
			else if (state[i] == 5){	score += abs(i/3 - FIVE/3)  + abs(i%3 - FIVE%3); }
			
			else if (state[i] == 6){	score += abs(i/3 - SIX/3)  + abs(i%3 - SIX%3); }
			
			else if (state[i] == 7){	score += abs(i/3 - SEVEN/3)  + abs(i%3 - SEVEN%3); }
			
			else if (state[i] == 8){	score += abs(i/3 - EIGHT/3)  + abs(i%3 - EIGHT%3); }
			
			else if (state[i] == 0){	score += abs(i/3 - BLANK/3)  + abs(i%3 - BLANK%3); }
		}
	}
	void tilereversal() 
	{
		//123
		//804
		//765
		score2 = 0 ;
		if (state[0] == 2 && (state[1] == 1))
		   score2 += 2;
		if (state[0] == 8 && (state[3] == 1))
			score2 += 2;
		if (state[1] == 3 && (state[2] == 2))
			score2 += 2;
		if (state[2] == 4 && (state[5] == 3))
			score2 += 2;
		if (state[3] == 7 && (state[6] == 8))
			score2 += 2;
		if (state[5] == 5 && (state[8] == 4))
			score2 += 2;
		if (state[6] == 6 && state[7] == 7)
			score2 += 2;
		if (state[7] == 5 && state[8] == 6)
			score2 += 2;
		
	}
	void updateScore()
	{
		manhattandistance(); //832105674
		tilereversal();
		score += score2 + depth;
	}
	void setDepth(int x) { depth = x; }
	int& getDepth() { return depth; }
	void generateStates(list<EightPuzzle> &new_states)
	{
		EightPuzzle t;
		//Basic Blank Swaps
		
		//First potential swap	
		//Creates a state
		if (swap(x, y, x + 1, y))
			new_states.push_back(EightPuzzle(state,x,y, x + 1, y));
		//Second Swap
		
		if (swap(x, y, x - 1, y))
			new_states.push_back(EightPuzzle(state,x, y, x-1,y));
		//Third Swap
		
		if (swap(x, y, x , y + 1))
			new_states.push_back(EightPuzzle(state, x ,y ,x, y + 1));
		//Fourth Swap
		
		if (swap(x, y, x , y - 1))
			new_states.push_back(EightPuzzle(state, x ,y, x, y - 1));
		//Fifth Swap
		
		if (swap(x, y, x + 1, y + 1))
			new_states.push_back(EightPuzzle(state, x ,y, x + 1,y + 1));
		//Sixth Swap
		
		if (swap(x, y, x + 1, y - 1))
			new_states.push_back(EightPuzzle(state, x, y, x + 1, y - 1));
		//Seventh Swap
		
		if (swap(x, y, x - 1 , y + 1))
			new_states.push_back(EightPuzzle(state,x, y , x-1,y+1));
		//Eighth Swap
		
		if (swap(x, y, x - 1, y - 1))
			new_states.push_back(EightPuzzle(state, x , y , x - 1, y - 1));
		

		if (swap3(0, 0, 2 , 1))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(0,0,2,1);
			new_states.push_back(t);
		}
		if (swap3(0, 0, 1, 2))
		{		
			t = EightPuzzle(state, x, y);
			t.swap2(0, 0, 1, 2 );
			new_states.push_back(t);
		}

		if (swap3(1, 0, 1, 2))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(1,0,1,2);
			new_states.push_back(t);
		}
		if (swap3(1,0,2,2))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(1,0,2,2);
			new_states.push_back(t);
		}
		if (swap3(2,0,0,1))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(2,0,0,1);
			new_states.push_back(t);
		}
		if (swap3(2,0,1,2))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(2,0,1,2);
			new_states.push_back(t);
		}
		if (swap3(0,1,2,2))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(0,1,2,2);
			new_states.push_back(t);
		}
		if (swap3(2,1,0,2))
		{
			t = EightPuzzle(state, x, y);
			t.swap2(2,1,0,2);
			new_states.push_back(t);
		}
		
	}

};
#endif