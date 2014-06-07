#pragma once
#include "cellautomata.h"
#include "parserFunction.h"
#include <cstdlib>
#include <iostream>
using namespace nameParser;
using namespace std;

namespace CellAuto
{
	enum Nbrhd {NEUMANN, MOORE, MVON, USER};

	class CellAuto2D : public CellAutomata
	{
		Nbrhd nbrhd;
		void Next();
		char *formula;
		bool error;

		int width;
		int height;

	public:
		CellAuto2D(void);
		CellAuto2D(int _width, int _height, Nbrhd _nbrhd):CellAutomata(width*height) 
		{
			nbrhd = _nbrhd;
			width = _width;
			height = _height;
		}
		~CellAuto2D(void);
		void GetNextConf();
		void SetTestConf();
		void SetRndConf();
		int GetCell(int i, int j);
		void SetDim(int, int);
		void SetNbrhd(Nbrhd _nbrhd);
		void ChangeCell(int i, int j);
		
		void ChangeFormula(char *str);
		int getError();
	};
}