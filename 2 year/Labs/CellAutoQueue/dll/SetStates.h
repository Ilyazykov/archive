#pragma once
#include "state.h"
#include <iostream>
using namespace std;

namespace CellAuto
{
	class SetStates
	{
		state *states;
		int num;
	public:
		SetStates(int n = 5);
		~SetStates(void);
		state& operator[] (int _num);
		void operator= (SetStates&);
		void copy(SetStates&);
	};
}