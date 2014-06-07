#pragma once
#include "list.h"
#include <iostream>
using namespace std;

namespace nameParser
{
	class doubleStack
	{
		list *beginNum[2];
	public:
		doubleStack(void);
		~doubleStack(void);
		bool isEmpty(int);
		bool isFull(int);
		void Push(char, int);
		char Pop(int);

		char see(int i) {if (beginNum[i]!=NULL) return beginNum[i]->key;}
	};
}