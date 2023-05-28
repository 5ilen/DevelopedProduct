#ifndef ConveyorH
#define ConveyorH
#include <vector>
#include <utility>

#define NN	-1	// Not Null
#define DC	-2	// Dont' care
using namespace std;

class cState
{
private:
	vector<bool> Q;		// Motor - run/suspend
	vector<int> I;		// Boxes - is something in box
	vector<bool> newQ;
	vector<int> newI;


public:
	cState(vector<bool> _Q, vector<int> _I, vector<bool> _newQ, vector<int> _newI) 
		{ Q = _Q; I = _I; newQ = _newQ; newI = _newI; }
	bool eq(vector<bool> sQ, vector<int> sI);
	vector<bool> getQ() { return Q; }
	vector<int> getI() { return I; }
	vector<bool> getNewQ() { return newQ; }
	vector<int> getNewI() { return newI; }
};

class Conveyor
{
private:
	vector<cState> cvs;

	vector<bool> stateQ;
	vector<int> stateI;
	vector<bool> chgQ;
	vector<bool> chgI;


public:
	void addState(cState _state) { cvs.push_back(_state); }

	void setState(vector<bool> _Q, vector<int> _I);
	bool step();

	cState getStateTab(int n) { return cvs[n];	};
	vector<bool> getStateQ() { return stateQ; }
	vector<int> getStateI() { return stateI; }
	vector<bool> getChangeQ() { return chgQ; }
	vector<bool> getChangeI() { return chgI; }
};

#endif