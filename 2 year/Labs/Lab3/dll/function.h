#pragma once
#include "doubleStack.h"
#include "intStack.h"

namespace nameParser
{
	struct variables
	{
		int A, B, C, D, E, F, G, H;
	};

	int Parser(char* str, variables &var); // �������

	int priority(char simbol); // ������� ��������
	void parser(doubleStack &stack, char *&str);
	int equence(doubleStack &stack, variables var);

	int value(char &symbol, variables &var, intStack &istack); // ������� ��������
	int count(int a, char symbol, int b); // ������� ��������
}