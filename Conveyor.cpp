#include "pch.h"
#include "Conveyor.h"

bool cState::eq(vector<bool> sQ, vector<int> sI)
{
	for (size_t i = 0; i < Q.size(); i++) if (sQ[i] != Q[i]) return false;
	for (size_t i = 0; i < I.size(); i++) 
		if ((I[i]!=DC) && 
			((I[i] == NN && sI[i]<=0) || (I[i]==0 && sI[i]!=0) || (I[i] == 1 && sI[i] == 0))) return false;

	return true;
}

void Conveyor::setState(vector<bool> _Q, vector<int> _I)
{ 
	stateQ = _Q; stateI = _I; 
	chgQ.clear(); chgI.clear();
	for (auto x : stateQ) chgQ.push_back(true);
	for (auto x : stateI) chgI.push_back(true);
}

bool Conveyor::step()
{
	vector<bool> newQ; int x = stateI[0];
	vector<int> newI;
	for (auto st : cvs)
		if (st.eq(stateQ,stateI)) {
			newQ = st.getNewQ();
			newI = st.getNewI();
			break;
		}

	if (!newQ.size()) return false;

	chgQ.clear(); chgI.clear();
	for (size_t i = 0; i < stateQ.size(); i++) chgQ.push_back(stateQ[i] != newQ[i]);
	for (size_t i = 0; i < stateI.size(); i++) {
		newI[i] = stateI[i] + newI[i];
		chgI.push_back(stateI[i] != newI[i]);
	}

	stateQ = newQ; stateI = newI;
	return true;
}
