#include "intStack.h"

namespace nameParser
{
	intStack::intStack(void)
	{
		beginNum = NULL;
	}

	intStack::~intStack(void)
	{
		while (beginNum)
		{
			intList *temp = beginNum;
			beginNum = beginNum->next;
			delete temp;
		}
	}

	bool intStack::isEmpty()
	{
		return (!beginNum);
	}

	bool intStack::isFull()
	{
		bool res;
		list* temp = new list;

		if (temp) res = false;
		else res = true;

		delete temp;

		return res;
	}

	void intStack::Push(int elem)
	{
		if (isFull()) return;

		intList *temp = new intList;
		temp->next = beginNum;
		temp->key = elem;

		beginNum = temp;
	}

	int intStack::Pop()
	{
		if (isEmpty()) return 'q';

		char res = beginNum->key;
		intList *temp = beginNum;
		beginNum = beginNum->next;

		delete temp;

		return res;
	}
}