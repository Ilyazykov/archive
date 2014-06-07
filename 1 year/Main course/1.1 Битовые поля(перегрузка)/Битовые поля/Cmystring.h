#pragma once
#include <fstream>
using namespace std;

class Cmystring
{
	char* str; // строка
	int size; // размер
	int leng; // длина
public:
	Cmystring(void);					// По умолчанию
	Cmystring(int _leng, char fill);	// Инициализатор
	Cmystring(const Cmystring& cms);	// Копирования
	Cmystring(const char* cstr);		// Преобразования типа
	~Cmystring(void);					// Деструктор

	Cmystring& operator =(const Cmystring& _str);	// присваивание
	Cmystring& operator =(const char* cstr);		// присваивание
	Cmystring& operator+=(const Cmystring& _str);	// +присваив.
	Cmystring& operator+=(const char* cstr);		// +присваив.
	Cmystring& operator +(const Cmystring& _str);	// объединение
	Cmystring& operator +(const char* cstr);		// объединение
	bool	   operator==(const char* cstr);		// сравнение
	bool operator==(const Cmystring& _str) const;	// сравнение
	char& operator[](int index);					// индексация
	const char& Cmystring::operator[](int index) const;
	friend Cmystring& operator +(const char* cstr, const Cmystring& _str);

	friend ostream& operator<<(ostream& stream, const Cmystring& _str);
	friend istream& operator>>(istream& stream,       Cmystring& _str);

private:
	void _copy(const char* cstr); // копирование строки в себя
};