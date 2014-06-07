#pragma once
#include "doubleStack.h"
#include "intStack.h"

namespace nameParser
{
	struct variables
	{
		int A, B, C, D, E, F, G, H, I, J, K, L, M;
	};

	class parserFunction
	{
		int priority(char simbol); // придётся изменять
		void parser(doubleStack &stack, char *&str);
		int equence(doubleStack &stack, variables var);

		int value(char &symbol, variables &var, intStack &istack); // придётся изменять
		int count(int a, char symbol, int b); // придётся изменять
	public:
		parserFunction(void);
		~parserFunction(void);

		bool foolproof(char* str);
		int Parser(char* str, variables &var); // главная
	};
}

