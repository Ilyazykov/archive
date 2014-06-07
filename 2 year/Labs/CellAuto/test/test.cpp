#include <iostream>
#include "../dll/state.cpp"
#include "../dll/SetStates.cpp"
#include "../dll/CellAutomata.cpp"
#include "../dll/CellAuto2D.cpp"

using namespace std;
using namespace CellAuto;

void output(CellAuto2D &test, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << test.GetCell(i, j) << '\t';
		cout << endl;
	}
}

void main()
{
	int size = 5;

	CellAuto2D test(size, Nbrhd::NEUMANN);

	test.SetTestConf();
	output(test, size);

	cout << endl;

	test.GetNextConf();
	output(test, size);

	cout << endl;

	test.GetNextConf();
	output(test, size);

	cout << endl;

	test.GetNextConf();
	output(test, size);
}