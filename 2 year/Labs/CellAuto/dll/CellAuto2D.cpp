#include "CellAuto2D.h"

#include <iostream>
using namespace std;

namespace CellAuto
{
	CellAuto2D::CellAuto2D(void)
	{
		dim = 0;
	}

	CellAuto2D::~CellAuto2D(void)
	{
	}

	void CellAuto2D::Next()
	{
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
			{
				int temp = 0;

				if (nbrhd == 0)
				{
					for (int d = -1; d < 2; d++) 
					{
						if (i + d >= 0 && i + d < dim) temp ^= comConf[(i + d) * dim + j];
					}
					if (j - 1 >= 0) temp ^= comConf[i * dim + j - 1];
					if (j + 1 < dim) temp ^= comConf[i * dim + j + 1];
				}

				else if (nbrhd == 1)
				{
					for (int di = -1; di < 2; di++) 
						for (int dj = -1; dj < 2; dj++) 
							if (i + di >= 0 && i + di < dim && j + dj >= 0 && j + dj < dim) temp ^= comConf[(i + di)*dim + (j + dj)];
				}

				else
				{
					for (int di = -1; di < 2; di++) 
						for (int dj = -1; dj < 2; dj++) 
							if (i + di >= 0 && i + di < dim && j + dj >= 0 && j + dj < dim)
								temp ^= comConf[(i + di)* dim + (j + dj)];
					if (i - 2 >= 0) temp ^= comConf[(i - 2) * dim + j];
					if (i + 2 < dim) temp ^= comConf[(i + 2) * dim + j];
					if (j - 2 >= 0) temp ^= comConf[i * dim + (j - 2)];
					if (j + 2 < dim) temp ^= comConf[i * dim + (j + 2)];
				}

				if (temp) newConf[i * dim + j] = 1;
				else newConf[i * dim + j] = 0;

			}
	}

	void CellAuto2D::SetTestConf()
	{
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
				comConf[i * dim + j] = 0;

		int temp = dim / 2;
		comConf[temp * dim + temp] = 1;
		Next();
	}

	void CellAuto2D::SetRndConf()
	{
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
				comConf[i * dim + j] = rand()%2;
		Next();
	}

	void CellAuto2D::GetNextConf()
	{
		comConf = newConf;
		Next();
	}

	int CellAuto2D::GetCell(int i, int j)
	{
		return comConf[i * dim + j];
	}

	void CellAuto2D::SetDim(int _dim)
	{
		dim = _dim;
		SetStates comConfTemp(dim * dim);
		SetStates newConfTemp(dim * dim);

		comConf = comConfTemp;
		newConf = newConfTemp;
	}

	void CellAuto2D::ChangeCell(int i, int j)
	{
		if (i >= 0 && i < dim && j >= 0 && j < dim)
		{
			if (comConf[i * dim + j]) comConf[i * dim + j] = 0;
			else comConf[i * dim + j] = 1;
		}
		Next();
	}

	void CellAuto2D::SetNbrhd(Nbrhd _nbrhd)
	{
		nbrhd = _nbrhd;
		Next();
	}
}