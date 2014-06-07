#pragma once
#include <fstream>
using namespace std;

class Cmystring
{
	char* str; // ������
	int size; // ������
	int leng; // �����
public:
	Cmystring(void);					// �� ���������
	Cmystring(int _leng, char fill);	// �������������
	Cmystring(const Cmystring& cms);	// �����������
	Cmystring(const char* cstr);		// �������������� ����
	~Cmystring(void);					// ����������

	Cmystring& operator =(const Cmystring& _str);	// ������������
	Cmystring& operator =(const char* cstr);		// ������������
	Cmystring& operator+=(const Cmystring& _str);	// +��������.
	Cmystring& operator+=(const char* cstr);		// +��������.
	Cmystring& operator +(const Cmystring& _str);	// �����������
	Cmystring& operator +(const char* cstr);		// �����������
	bool	   operator==(const char* cstr);		// ���������
	bool operator==(const Cmystring& _str) const;	// ���������
	char& operator[](int index);					// ����������
	const char& Cmystring::operator[](int index) const;
	friend Cmystring& operator +(const char* cstr, const Cmystring& _str);

	friend ostream& operator<<(ostream& stream, const Cmystring& _str);
	friend istream& operator>>(istream& stream,       Cmystring& _str);

private:
	void _copy(const char* cstr); // ����������� ������ � ����
};