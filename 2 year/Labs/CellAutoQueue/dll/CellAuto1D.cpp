#include "CellAuto1D.h"

#include <iostream>
using namespace std;

namespace CellAuto
{
	CellAuto1D::CellAuto1D(void)
	{
		dim = 0;
	}

	CellAuto1D::~CellAuto1D(void)
	{
	}

	void CellAuto1D::Next()
	{
		for (int i = 0; i < dim; i++)
			{
				int temp = 0;

				if (nbrhd == 0)
				{
					for (int d = -1; d < 2; d++) 
					{
						if (i + d >= 0 && i + d < dim) temp ^= comConf[i + d];
					}
				}
				else
				{
					for (int d = -2; d < 3; d++) 
					{
						if (i + d >= 0 && i + d < dim) temp ^= comConf[i + d];
					}
				}
				if (temp) newConf[i] = 1;
				else newConf[i] = 0;
			}
	}

	void CellAuto1D::SetTestConf()
	{
		for (int i = 0; i < dim; i++)
			comConf[i] = 0;

		int temp = dim / 2;
		comConf[temp] = 1;
		Next();
	}

	void CellAuto1D::SetRndConf()
	{
		for (int i = 0; i < dim; i++)
				comConf[i] = rand()%2;
		Next();
	}

	void CellAuto1D::GetNextConf()
	{
		comConf = newConf;
		Next();
	}

	int CellAuto1D::GetCell(int i)
	{
		return comConf[i];
	}

	void CellAuto1D::SetDim(int _dim)
	{
		dim = _dim;
		SetStates comConfTemp(dim);
		SetStates newConfTemp(dim);

		comConf = comConfTemp;
		newConf = newConfTemp;
	}

	void CellAuto1D::ChangeCell(int i)
	{
		if (i >= 0 && i < dim)
		{
			if (comConf[i]) comConf[i] = 0;
			else comConf[i] = 1;
		}
		Next();
	}

	void CellAuto1D::SetNbrhd(Nbrhd _nbrhd)
	{
		nbrhd = _nbrhd;
		Next();
	}
}