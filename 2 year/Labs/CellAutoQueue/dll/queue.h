#pragma once
#include "CellAuto1D.h"

namespace CellAuto
{
	class myQueue
	{
		int **arr;
		int numOfString;
		int numCharInString;
		int Hi;
		int Li;
		int occupancy;
public:
		myQueue();
		myQueue(int, int);
		~myQueue();
		//CellAuto1D pop(void);
		int GetHi() {
			int temp = Hi - 1;
			if (temp == -1) temp = numOfString-1;
			return temp;
		}
		void push(CellAuto1D&);
		bool isEmpty();
		bool isFull();

		int viewElem(int numInQueue, int numInAutomata);
		void changeCell(int y);
	};
}