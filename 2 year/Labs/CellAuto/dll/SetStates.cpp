#include "SetStates.h"

namespace CellAuto
{
	SetStates::SetStates(int n)
	{
		num = n;
		states = new state[num];
	}

	SetStates::~SetStates(void)
	{
		delete [] states;
	}

	state& SetStates::operator[](int n)
	{
		return states[n];
	}

	void SetStates::operator= (SetStates& newState)
	{
		num = newState.num;

		delete [] states;
		states = new state[num];

		for (int i = 0; i < num; i++)
		{
			states[i] = newState.states[i];
		}
	}
}