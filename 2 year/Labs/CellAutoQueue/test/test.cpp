#include <iostream>
#include "../dll/state.cpp"
#include "../dll/SetStates.cpp"
#include "../dll/CellAutomata.cpp"
#include "../dll/CellAuto2D.cpp"
#include "../dll/CellAuto1D.cpp"
#include "../dll/queue.cpp"

using namespace std;
using namespace CellAuto;

void outputQueue(myQueue &queue, int numOfString, int numCharInString)
{
	for (int i = 0; i < numOfString; i++)
	{
		for (int j = 0; j < numCharInString; j++)
			cout << queue.viewElem(i, j) << '\t';
		cout << endl;
	}
}

void outputCellAuto(CellAuto2D &test, int size)
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
	int numOfString = 2;
	int numCharInString = 5;

	CellAuto1D test(numCharInString, Nbrhd::NEUMANN);
	myQueue queue(numOfString, numCharInString);

	test.SetTestConf();
	queue.push(test);//?
	outputQueue(queue, numOfString, numCharInString);
	cout << endl;

	test.GetNextConf();
	queue.push(test);
	outputQueue(queue, numOfString, numCharInString);
	cout << endl;

	test.GetNextConf();
	queue.push(test);
	outputQueue(queue, numOfString, numCharInString);
}