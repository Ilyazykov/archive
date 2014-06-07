#pragma once

#include "Cmystring.h"

#include <iostream>
using namespace std;

class TBitFields
{
	unsigned* field; // битовое поле

	int fCount; // количество полей
	int size; // размер (в байтах)

	Cmystring* fNames; // названия полей
	char* fSizes; // размер полей (в битах)
	char* fIndex; // адреса начала полей (в битах)
	char* fPos; // положение поля в массиве fields

public:
	// Конструкторы ---------------------------------
	TBitFields(int _fCount, Cmystring* _fNames, char* _fSizes);
	// Деструктор -----------------------------------
	~TBitFields(void);
	// установить значение поля
	void SetField(const Cmystring _fName, unsigned fVals);
	// получить значение поля
	unsigned GetField(const Cmystring _fName);
	unsigned GetField(const Cmystring _fName) const;
	// прибавить значение к полю
	void AddField(const Cmystring _fName, unsigned fVals);
	friend ostream& operator<<(ostream& stream, const TBitFields& _bf);
	//friend istream& operator>>(istream& stream,       TBitFields& _bf);

	void see();

private:
	void _copy(unsigned fVals, int i);
	unsigned _get(int i);
	unsigned _get(int i) const;
	int _findField(const Cmystring _fName) const;
};

