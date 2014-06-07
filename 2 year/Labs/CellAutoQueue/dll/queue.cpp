#include "queue.h"

namespace CellAuto
{
	myQueue::myQueue()
	{
		numOfString = 0;
		//arr = NULL;
	}

	myQueue::myQueue(int _numOfString, int _numCharInString)
	{
		numOfString = _numOfString;
		numCharInString = _numCharInString;

		//numOfString = numCharInString;//temprorary

		arr = new int*[numOfString];
		for (int i = 0; i < numOfString; i++)
		{
			arr[i] = new int[numCharInString];
			for (int j = 0; j < numCharInString; j++)
			{
				arr[i][j] = 0;
			}
		}

		Hi = 0;
		Li = 0;
		occupancy = 0;
	}

	myQueue::~myQueue()
	{
		for (int i= 0; i<numOfString; i++)
		{
			delete [] arr[i];
		}

		delete [] arr;
		arr = NULL;
	}

	bool myQueue::isEmpty()
	{
		return (!occupancy);
	}

	bool myQueue::isFull()
	{
		return (occupancy == numOfString);
	}

	void myQueue::push(CellAuto1D &elem)
	{
		for (int i = 0; i < numCharInString; i++)
		{
			arr[Hi][i] = elem.GetCell(i);
		}
		
		Hi++;
		if (Hi == numOfString) Hi = 0;
	}

	int myQueue::viewElem(int numInQueue, int numInAutomata)
	{
		return arr[numInQueue][numInAutomata];
	}

	void myQueue::changeCell(int y)
	{
		int temp = Hi-1;
		if (temp<0) temp = numOfString - 1; 
		if (arr[temp][y]) arr[temp][y]=0;
		else arr[temp][y]=1;
	}
}