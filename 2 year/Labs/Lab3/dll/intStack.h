#pragma once
#include "list.h"
#include <iostream>
using namespace std;

namespace nameParser
{
	class intStack
	{
		intList *beginNum;
	public:
		intStack(void);
		~intStack(void);

		bool isEmpty();
		bool isFull();
		void Push(int);
		int Pop();
	};
}

