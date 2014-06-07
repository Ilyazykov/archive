#include "Cmystring.h"

Cmystring::Cmystring(void)
{
	leng = 0; size = 0; str = 0;
}

Cmystring::Cmystring(int _leng, char fill)
{
	leng = _leng; 
	size = _leng + 1; 
	str = new char[size];
	for (int i = 0; i < leng; i++) str[i] = fill;
	str[leng] = 0;
}

Cmystring::Cmystring(const Cmystring& cms)
{
	size = 0; leng = 0; 
	_copy(cms.str);
}

Cmystring::Cmystring(const char* cstr)
{
	size = 0; leng = 0; 
	_copy(cstr);
}

Cmystring::~Cmystring(void)
{
	if (str) delete str;
	size = 0; leng = 0; str = 0;
}

void Cmystring::_copy(const char* cstr)
{
	int s_cstr = 0; while (cstr[s_cstr++]);
	if (str == 0 || size < s_cstr)
	{
		if (leng > 0) delete[] str;
		if (size < s_cstr) size = s_cstr;
		str = new char[size];
	}
	leng = 0;
	while (str[leng] = cstr[leng]) leng++;
}

Cmystring& Cmystring::operator =(const Cmystring& _str)
{
	if (this != &_str) _copy(_str.str);
	return *this;
}

Cmystring& Cmystring::operator =(const char* cstr)
{
	_copy(cstr);
	return *this;
}

Cmystring& Cmystring::operator +(const Cmystring& _str)
{
	Cmystring tmp(leng + _str.leng, ' ');
	tmp._copy(str);
	int i = 0;
	while (tmp.str[leng+i] = _str.str[i]) i++;
	tmp.leng = leng + _str.leng;
	return tmp;
}

Cmystring& Cmystring::operator +(const char* cstr)
{
	int i = 0; while (cstr[i]) i++;
	Cmystring tmp(leng + i, ' ');
	tmp._copy(str);
	i = 0;
	while (tmp.str[leng+i] = cstr[i]) i++;
	tmp.leng = leng + i;
	return tmp;
}

Cmystring& Cmystring::operator+=(const Cmystring& _str)
{
	int i = 0;
	if (leng + _str.leng > size)
	{
		size = leng + _str.leng + 1;
		char *tmp = new char[size];
		while (tmp[i] = str[i]) i++;
		delete[] str;
		str = tmp;
	}
	i = 0;
	while (str[leng+i] = _str.str[i]) i++;
	leng = leng + i - 1;
	return *this;
}

Cmystring& Cmystring::operator+=(const char* cstr)
{
	char *tmp = (*this + cstr).str;
	_copy(tmp);
	return *this;
}

Cmystring& operator +(const char* cstr, const Cmystring& _str)
{
	int i = 0; while (cstr[i]) i++;
	Cmystring tmp(_str.leng + i, ' ');
	i = 0;
	while (tmp.str[i] = cstr[i]) i++;
	int j = 0;
	while (tmp.str[i+j] = _str.str[j]) j++;
	tmp.leng = i + j - 1;
	return tmp;
}

char& Cmystring::operator[](int index)
{
	return str[index];
}

const char& Cmystring::operator[](int index) const
{
	return str[index];
}

bool Cmystring::operator==(const Cmystring& _str) const
{
	bool rez = true;
	if (leng != _str.leng) rez = false;
	else 
	{
		for (int i = 0; i < leng && rez; i++)
			if ((*this)[i] != _str[i]) rez = false;
	}
	return rez;
}

ostream& operator<<(ostream& stream, const Cmystring& _str)
{
	stream << _str.str;
	return stream;
}

istream& operator>>(istream& stream,       Cmystring& _str)
{
	char ss[120];
	stream.getline(ss, 120);
	_str = ss;
	return stream;
}