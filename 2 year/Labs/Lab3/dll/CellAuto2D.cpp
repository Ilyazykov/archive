#include "CellAuto2D.h"

#include <iostream>
using namespace std;

namespace CellAuto
{
	CellAuto2D::CellAuto2D(void)
	{
		dim = 0;
		formula = "A+C+E+G";
		error = false;
	}

	CellAuto2D::~CellAuto2D(void)
	{
	}

	void CellAuto2D::Next()
	{
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
			{
				int temp = 0;

				if (nbrhd == 0)
				{
					for (int d = -1; d < 2; d++) 
					{
						if (i + d >= 0 && i + d < width) temp ^= comConf[(i + d) + j * width];
					}
					if (j - 1 >= 0) temp ^= comConf[i + (j - 1) * width];
					if (j + 1 < height) temp ^= comConf[i + (j + 1) * width];

					if (temp) newConf[i + j * width] = 1;
					else newConf[i + j * width] = 0;
				}

				else if (nbrhd == 1)
				{
					for (int di = -1; di < 2; di++) 
						for (int dj = -1; dj < 2; dj++) 
							if (i + di >= 0 && i + di < width && j + dj >= 0 && j + dj < height) temp ^= comConf[(i + di) + (j + dj)*width];
					
					if (temp) newConf[i + j * width] = 1;
					else newConf[i + j * width] = 0;
				}

				else if (nbrhd == 2)
				{
					for (int di = -1; di < 2; di++) 
						for (int dj = -1; dj < 2; dj++) 
							if (i + di >= 0 && i + di < width && j + dj >= 0 && j + dj < height)
								temp ^= comConf[(i + di) + (j + dj) * width];
					if (i - 2 >= 0) temp ^= comConf[(i - 2) + j * width];
					if (i + 2 < width) temp ^= comConf[(i + 2) + j * width];
					if (j - 2 >= 0) temp ^= comConf[i + (j - 2) * width];
					if (j + 2 < height) temp ^= comConf[i + (j + 2) * width];

					if (temp) newConf[i + j * width] = 1;
					else newConf[i + j * width] = 0;
				}

				else 
				{
					parserFunction par;
					error = par.foolproof(formula);
					if (error) 
					{
						newConf[i + j * width] = comConf[i + j * width];
						break;
					}
					
					variables var;
#pragma region var
					var.A = 0; var.B = 0; var.C = 0; var.D = 0; var.E = 0; var.F = 0; var.G = 0; var.H = 0;
					var.I = 0; var.J = 0; var.K = 0; var.L = 0; var.M = 0;

					if (i - 2 >= 0) var.A = comConf[(i - 2) + j * width];
					if (j - 2 >= 0) var.C = comConf[i + (j - 2) * width];
					if (i + 2 < width) var.E = comConf[(i + 2) + j * width];
					if (j + 2 < height) var.G = comConf[i + (j + 2) * width];
					var.M = comConf[i + j * width];

					if (i - 1 >= 0) var.I = comConf[(i - 1) + j * width];
					if (i - 1 >=0 && j - 1 >= 0 ) var.B = comConf[(i - 1) + (j - 1) * width];
					if (j - 1 >= 0) var.J = comConf[i + (j - 1) * width];
					if (i + 1 < width && j - 1 >= 0 ) var.D = comConf[(i + 1) + (j - 1) * width];
					if (i + 1 < width) var.K = comConf[(i + 1) + j * width];
					if (i + 1 < width && j + 1 < height ) var.F = comConf[(i + 1) + (j + 1) * width];
					if (j + 1 < height) var.L = comConf[i + (j + 1) * width];
					if (i - 1 >=0 && j + 1 < height ) var.H = comConf[(i - 1) + (j + 1) * width];
#pragma endregion
					newConf[i + j * width] = par.Parser(formula, var);
				}
			}
	}

	void CellAuto2D::SetTestConf()
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				comConf[i + j * width] = 0;

		comConf[(width / 2) + (height / 2) * width] = 1;
		Next();
	}

	void CellAuto2D::SetRndConf()
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				comConf[i + j * width] = rand()%2;
		Next();
	}

	void CellAuto2D::GetNextConf()
	{
		comConf = newConf;
		Next();
	}

	int CellAuto2D::GetCell(int i, int j)
	{
		return comConf[i + j * width];
	}

	void CellAuto2D::SetDim(int _width, int _height)
	{
		width = _width;
		height = _height;

		SetStates comConfTemp(width * height);
		SetStates newConfTemp(width * height);

		comConf = comConfTemp;
		newConf = newConfTemp;
	}

	void CellAuto2D::ChangeCell(int i, int j)
	{
		if (i >= 0 && i < width && j >= 0 && j < height)
		{
			int temp = comConf[i + j * width];
			if (comConf[i + j * width] == 2) temp = 0;
			else temp++;

			comConf[i + j * width] = temp;
		}
		Next();
	}

	void CellAuto2D::SetNbrhd(Nbrhd _nbrhd)
	{
		nbrhd = _nbrhd;
		Next();
	}

	void CellAuto2D::ChangeFormula(char *str)
	{
		formula = str;
		Next();
	}

	int CellAuto2D::getError()
	{
		return error;
	}
}