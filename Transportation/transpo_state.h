#ifndef TRANSPO_STATE_H
#define TRANSPO_STATE_H
#include <list>
#include <iostream>
#include <string>

using namespace std;

class Transpo_State
{

private:
	int goats, tigers, hay, n;
	int score, depth;
public:	
	
	Transpo_State()
	{
		goats = 3;
		tigers = 3;
		hay = 3;
		n = 3;
		score = 0;
		depth = 0;
	}

	Transpo_State(int m)
	{
		goats = m;
		tigers = m;
		hay = m;
		n = m;
		score = 0;
		depth = 0;
	}

	Transpo_State(int h, int g, int t, int m)
	{
		goats = g;
		tigers = t;
		hay = h;
		n = m;
		score = 0;
		depth = 0;
	}
	
	 int getGoats() { return goats;}
	 int getTigers() { return tigers;}
	 int getHay(){ return hay; }
	 int toInteger() { return (goats * 100) + (hay * 10) + tigers ;}

	 bool isValid()
	 {
		bool valid = true;
		// The rules for an undercontrol move
		if ( goats < 0 || hay < 0 || tigers < 0) { valid = false; }

		if ( goats > hay && hay != 0) { valid = false; }

		if ( (n-goats) > (n-hay) && (n-hay) != 0 ) { valid = false; }

		if ( tigers > (goats + hay) && goats != 0 ) { valid = false; }
			 
		if ( (n - tigers) > (2 * n - goats - hay)  && goats != 0) { valid = false; }

		return valid;
	 }
	
	 bool goalstate()
	{
		if ( (goats + tigers + hay) == 0) 
			return true;
		else
			return false;
	}

	 bool operator ==(Transpo_State &rhs) 
	 {
		if (goats == rhs.getGoats() && tigers == rhs.getTigers() && hay == rhs.getHay())
			return true;
		else
			return false;
	 }

	 bool operator >(Transpo_State &rhs)
	 {
		if (goats > rhs.getGoats() || (goats == rhs.getGoats() && hay > rhs.getHay()) || (goats ==rhs.getGoats() && hay == rhs.getHay() && tigers > rhs.getTigers()) )
			return true;
		 else 
			 return false; 
	 }
	 
	 bool operator <(Transpo_State &rhs)
	 {
		if (goats < rhs.getGoats() || (goats == rhs.getGoats() && hay < rhs.getHay()) || (goats ==rhs.getGoats() && hay == rhs.getHay() && tigers < rhs.getTigers()) )
			return true;
		 else 
			 return false; 
	 }

		/// Out Puts Sate Data
	 string print()
	 {
		char str[25];
		sprintf_s( str, "G: %d H: %d T: %d \n", goats, hay, tigers);
		string s(str);
		return s;
	 }

	 int getDepth () { return depth;}
	 void setDepth(int x) { depth = x; }
	 int getScore() {return score; }
	 void updateScore() 
	 {
		 // Heuristic 1
		 //score += hay + goats + tigers + depth;
		 // Heuristic 2
		 //score += 3 * tigers + depth;
		 // Heuristic 3 (Mix of minimizing tigers and minimizing overall)
		 score = 3 * tigers +  hay + goats + depth;
	 }

	 //Generates a large number of possible choices and then evaluates which ones are valid and returns them to the node list
	 void generateStates(list<Transpo_State> &validchoices )
	 {	
		
		list<Transpo_State> choices;

			choices.push_back(Transpo_State(hay-2,goats,tigers,n));
			choices.push_back(Transpo_State(hay,goats-2,tigers,n));
			choices.push_back(Transpo_State(hay,goats,tigers-2,n));
			
			choices.push_back(Transpo_State(hay - 1, goats - 1, tigers,n));
			choices.push_back(Transpo_State(hay - 1, goats, tigers -1,n ));
			choices.push_back(Transpo_State(hay, goats - 1,tigers- 1 , n));
			
			choices.push_back(Transpo_State(hay - 1, goats , tigers-1, n));
			choices.push_back(Transpo_State(hay,goats-1,tigers,n));			
			choices.push_back(Transpo_State(hay,goats,tigers-1,n));

		for (list<Transpo_State>::iterator it = choices.begin(); it!= choices.end(); ++it)
		{
			if ((*it).isValid())
			{
			 validchoices.push_back(*it);
			}
		}
	 }

	
	 
	
	
	
};

#endif


 