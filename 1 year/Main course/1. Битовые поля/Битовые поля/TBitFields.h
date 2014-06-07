#pragma once

#include "Cmystring.h"

#include <iostream>
using namespace std;

class TBitFields
{
	unsigned* field; // ������� ����

	int fCount; // ���������� �����
	int size; // ������ (� ������)

	Cmystring* fNames; // �������� �����
	char* fSizes; // ������ ����� (� �����)
	char* fIndex; // ������ ������ ����� (� �����)
	char* fPos; // ��������� ���� � ������� fields

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

private:
	void _copy(unsigned fVals, int i);
	unsigned _get(int i);
	unsigned _get(int i) const;
	int _findField(const Cmystring _fName) const;
};

