#include "state.h"

namespace CellAuto
{
	state::state(void)
	{
		stat = 0;
	}

	state::state(int n)
	{
		stat = n;
	}

	state::~state(void)
	{
	}

	int  state::operator=	(const int& n)
	{
		stat = n;
		return stat;
	}

	int state::operator== (const int& n)
	{
		return (stat == n);
	}
}