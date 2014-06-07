#include "doubleStack.h"

namespace nameParser
{
	doubleStack::doubleStack(void)
	{
		beginNum[0] = NULL;
		beginNum[1] = NULL;
	}

	doubleStack::~doubleStack(void)
	{
		for (int i = 0; i < 2; i++)
		{
			while (beginNum[i])
			{
				list *temp = beginNum[i];
				beginNum[i] = beginNum[i]->next;
				delete temp;
			}
		}
	}

	bool doubleStack::isEmpty(int i)
	{
		return (!beginNum[i]);
	}

	bool doubleStack::isFull(int i)
	{
		bool res;
		list* temp = new list;

		if (temp) res = false;
		else res = true;

		delete temp;

		return res;
	}

	void doubleStack::Push(char elem, int i)
	{
		if (isFull(i)) return;

		list *temp = new list;
		temp->next = beginNum[i];
		temp->key = elem;

		beginNum[i] = temp;
	}

	char doubleStack::Pop(int i)
	{
		if (isEmpty(i)) return 'q';

		char res = beginNum[i]->key;
		list *temp = beginNum[i];
		beginNum[i] = beginNum[i]->next;

		delete temp;

		return res;
	}
}