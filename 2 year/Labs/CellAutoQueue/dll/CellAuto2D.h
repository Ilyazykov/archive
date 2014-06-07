#pragma once
#include "cellautomata.h"
#include <cstdlib>

namespace CellAuto
{
	enum Nbrhd {NEUMANN, MOORE, MVON};

	class CellAuto2D : public CellAutomata
	{
		Nbrhd nbrhd;
		void Next();
	public:
		CellAuto2D(void);
		CellAuto2D(int dim, Nbrhd _nbrhd):CellAutomata(dim*dim) {nbrhd = _nbrhd;}
		~CellAuto2D(void);
		void GetNextConf();
		void SetTestConf();
		void SetRndConf();
		int GetCell(int i, int j);
		void SetDim(int _dim);
		void SetNbrhd(Nbrhd _nbrhd);
		void ChangeCell(int i, int j);
	};
}