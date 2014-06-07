#include "CellAutomata.h"

namespace CellAuto
{
	CellAutomata::CellAutomata(void)
	{
	}

	CellAutomata::CellAutomata(int _dim)
	{
		dim = _dim;
		SetStates comConfTemp(dim * dim);
		SetStates newConfTemp(dim * dim);

		comConf = comConfTemp;
		newConf = newConfTemp;
	}

	CellAutomata::~CellAutomata(void)
	{
	}
}
