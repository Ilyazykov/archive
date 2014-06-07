#pragma once

#include "Cmystring.h"

#include <iostream>
using namespace std;

class ProxyClassForTBitFields;

class TBitFields
{
	unsigned* field; // ������� ����

	int fCount; // ���������� �����
	int size; // ������ (� ������)

	Cmystring* fNames; // �������� �����
	char* fSizes; // ������ ����� (� �����)
	char* fIndex; // ������ ������ ����� (� �����)
	char* fPos; // ��������� ���� � �������

public:
	// ������������ ---------------------------------

	TBitFields(int _fCount, Cmystring* _fNames, char* _fSizes);
	// ���������� -----------------------------------
	~TBitFields(void);
	// ���������� �������� ����
	void SetField(const Cmystring _fName, unsigned fVals);
	// �������� �������� ����
	unsigned GetField(const Cmystring _fName);
	unsigned GetField(const Cmystring _fName) const;
	// ��������� �������� � ����
	void AddField(const Cmystring _fName, unsigned fVals);
	friend ostream& operator<<(ostream& stream, const TBitFields& _bf);
	//friend istream& operator>>(istream& stream,       TBitFields& _bf);

	void see();

	ProxyClassForTBitFields operator[](const Cmystring _fName);

private:
	void _copy(unsigned fVals, int i);
	unsigned _get(int i);
	unsigned _get(int i) const;
	int _findField(const Cmystring _fName) const;
};

class ProxyClassForTBitFields
{
	TBitFields *bf;
	Cmystring fName;	
public:
	ProxyClassForTBitFields(TBitFields* _bf, Cmystring _fName) { bf = _bf; fName=_fName; }

	friend ostream& operator<< (ostream& stream, const ProxyClassForTBitFields PrBf);

	ProxyClassForTBitFields& operator=(const unsigned fVal);
	ProxyClassForTBitFields& operator=(const ProxyClassForTBitFields ob);

	friend unsigned operator+(ProxyClassForTBitFields ob1, ProxyClassForTBitFields ob2);
	friend unsigned operator+(unsigned fVals, ProxyClassForTBitFields ob);

	friend unsigned operator-(ProxyClassForTBitFields ob1, ProxyClassForTBitFields ob2);
	friend unsigned operator-(unsigned fVals, ProxyClassForTBitFields ob);

	friend unsigned operator*(ProxyClassForTBitFields ob1, ProxyClassForTBitFields ob2);
	friend unsigned operator*(ProxyClassForTBitFields ob, unsigned fVals);

	friend unsigned operator/(ProxyClassForTBitFields ob1, ProxyClassForTBitFields ob2);
	friend unsigned operator/(unsigned fVals, ProxyClassForTBitFields ob);
};
