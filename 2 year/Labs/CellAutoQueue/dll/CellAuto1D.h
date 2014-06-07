#pragma once
#include "cellautomata.h"
#include <cstdlib>
#include "CellAuto2D.h"

namespace CellAuto
{
	//enum Nbrhd {NEUMANN, MOORE, MVON};

	class CellAuto1D : public CellAutomata
	{
		Nbrhd nbrhd;
		void Next();
	public:
		CellAuto1D(void);
		CellAuto1D(int dim, Nbrhd _nbrhd):CellAutomata(dim) {nbrhd = _nbrhd;}
		~CellAuto1D(void);
		void GetNextConf();
		void SetTestConf();
		void SetRndConf();
		int GetCell(int i);
		void SetDim(int _dim);
		void SetNbrhd(Nbrhd _nbrhd);
		void ChangeCell(int i);
	};
}