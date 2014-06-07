#include "function.h"

namespace nameParser
{
	int Parser(char* str, variables &var)
	{
		doubleStack stack;
		parser(stack, str);
		return equence(stack, var);
	}

	int count(int a, char symbol, int b)
	{
		int res;

		switch (symbol)
		{
		case '+':
			res = (a + b) % 3;
			break;
		case '-':
			res = (3 + a - b) % 3;
			break;
		case '*':
			res = (a * b) % 3;
			break;
		case '/':
			if (b!=0) res = (a / b) % 3;
			else res = 0;
			break;
		default:
			res = 0;
		}
		return res;
	}

	int priority(char simbol)
	{
		if (simbol == '(') return 1;
		else if (simbol == '+' || simbol == '-') return 2;
		else if (simbol == '*' || simbol == '/') return 3;
		return 0;
	}

	void parser(doubleStack &stack, char *&str)
	{
		for (int i = 0; str[i] != '\0'; i++ )
		{
			if (str[i] >= 'A' && str[i] <= 'Z') stack.Push(str[i], 0);
			else if (str[i] == '(') stack.Push(str[i], 1);
			else if (str[i] == ')') 
			{
				do 
				{
					stack.Push(stack.Pop(1), 0);
				} while (stack.see(1) != '(');
				stack.Pop(1);
			}
			else 
			{
				if (!stack.isEmpty(1)) 
				{
					while (priority(str[i])<=priority(stack.see(1)))
					{
						stack.Push(stack.Pop(1), 0);
						if (stack.isEmpty(1)) break;
					}
				}
				stack.Push(str[i], 1);
			}
		}

		while (!stack.isEmpty(1)) stack.Push(stack.Pop(1), 0);
	}

	int equence(doubleStack &stack, variables var)
	{
		char symbol[3]; int a, b;
		symbol[1] = stack.Pop(0);
		symbol[2] = stack.Pop(0);
		symbol[0] = stack.Pop(0);

		int temp;
		intStack istack;

		do 
		{
			int ok = true;
			if (!(symbol[0]>='A' && symbol[0]<='Z')) ok = false;
			else if (!(symbol[1]=='+' || symbol[1]=='-' || symbol[1]=='*' || symbol[1]=='/')) ok = false;
			else if (!(symbol[2]>='A' && symbol[2]<='Z')) ok = false;

			if (ok) 
			{
				a = value(symbol[0], var, istack);
				b = value(symbol[2], var, istack);
				temp = count(a, symbol[1], b);

				stack.Push('X', 0);
				istack.Push(temp);

				while (!(stack.isEmpty(1))) stack.Push(stack.Pop(1), 0); 

				symbol[1] = stack.Pop(0);
				symbol[2] = stack.Pop(0);
			}
			else
			{
				stack.Push(symbol[1], 1);
				symbol[1] = symbol[2];
				symbol[2] = symbol[0];
			}
			symbol[0] = stack.Pop(0);
		} while (!(stack.isEmpty(0) && stack.isEmpty(1)));

		int ok = true;
		if (!(symbol[0]>='A' && symbol[0]<='Z')) ok = false;
		else if (!(symbol[1]=='+' || symbol[1]=='-' || symbol[1]=='*' || symbol[1]=='/')) ok = false;
		else if (!(symbol[2]>='A' && symbol[2]<='Z')) ok = false;

		if (ok) 
		{
			a = value(symbol[0], var, istack);
			b = value(symbol[2], var, istack);
			temp = count(a, symbol[1], b);
		}

		return temp;
	}

	int value(char &symbol, variables &var, intStack &istack)
	{
		int res;

		switch (symbol)
		{
		case 'A':
			res = var.A;
			break;
		case 'B':
			res = var.B;
			break;
		case 'C':
			res = var.C;
			break;
		case 'D':
			res = var.D;
			break;
		case 'E':
			res = var.E;
			break;
		case 'F':
			res = var.F;
			break;
		case 'G':
			res = var.G;
			break;
		case 'H':
			res = var.H;
			break;
		default:
			res = istack.Pop();
		}

		return res;
	}
}