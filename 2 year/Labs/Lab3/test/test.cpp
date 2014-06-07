#include <iostream>
#include "../dll/state.cpp"
#include "../dll/SetStates.cpp"
#include "../dll/CellAutomata.cpp"
#include "../dll/CellAuto2D.cpp"
#include "../dll/doubleStack.cpp"
#include "../dll/intStack.cpp"
#include "../dll/parserFunction.cpp"

using namespace std;
using namespace CellAuto;
using namespace nameParser;

void main()
{
	char *str = "(A+B)";

	variables var;
	var.A = 2; var.B = 2; var.C = 1; var.D = 2; var.F = 4; var.G = 3; var.H = 1;

	cout << str;

	parserFunction par;

	cout << endl;

	cout << par.foolproof(str) << endl;
}