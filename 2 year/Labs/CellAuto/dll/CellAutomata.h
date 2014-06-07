#pragma once
#include "SetStates.h"

namespace CellAuto
{
	class CellAutomata
	{
	protected:
		SetStates comConf;
		SetStates newConf;
		int dim;
	public:
		CellAutomata(void);
		CellAutomata(int n);
		~CellAutomata(void);
		virtual void GetNextConf() = 0;
		virtual void SetTestConf() = 0;
		virtual void SetRndConf() = 0;
	};
}