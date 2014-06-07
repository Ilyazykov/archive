#include "TBitFields.h"

TBitFields::TBitFields(int _fCount, Cmystring* _fNames, char* _fSizes)
{
	fCount = _fCount;
	fNames = new Cmystring[fCount];
	fSizes = new char[fCount];

	fPos = new char[fCount];
	fIndex = new char[fCount]; // содержит индексы начала битовых полей

	{
		char index = 0; // номер ячеейки (бит)

		char sizeCell = sizeof(unsigned)*8; // размер ячейки (4 байта)
		char numberCell = 0; // номер ячейки (4 байта)

		for (int i = 0; i < fCount; i++)
		{
			fNames[i] = _fNames[i];
			fSizes[i] = _fSizes[i];

			if (index + _fSizes[i] > sizeCell) 
			{
				index = sizeCell;
				numberCell++;
				sizeCell += sizeof(unsigned)*8;
			}

			fIndex[i] = index;
			index += _fSizes[i];

			fPos[i] = numberCell;
		}

		size = numberCell + 1;
	}

	field = new unsigned[size];
	for (int i = 0; i < size; i++) field[i] = 0;
}

TBitFields::~TBitFields(void)
{
	delete[] fNames;
	delete[] fSizes;
	delete[] fIndex;
	delete[] fPos;
	delete[] field;
}

void TBitFields::_copy(unsigned fVals, int i)
{
	unsigned mask = ~0;
	char left = fIndex[i] - fPos[i]*sizeof(unsigned)*8; // позиция слева от границы 4х байт
	char right = (fPos[i] + 1) * sizeof(unsigned) * 8 - fIndex[i] - fSizes[i]; // позиция справа от границы 4х байт

	mask <<= left;
	mask >>= left + right;
	mask <<= right;

	fVals <<= right;

	field[fPos[i]] = mask & field[fPos[i]] ^ mask & fVals ^ field[fPos[i]];
}



unsigned TBitFields::_get(int i)
{
	unsigned mask = ~0;
	char left = fIndex[i] - fPos[i]*sizeof(unsigned)*8; // позиция слева от границы 4х байт
	char right = (fPos[i] + 1) * sizeof(unsigned) * 8 - fIndex[i] - fSizes[i]; // позиция справа от границы 4х байт

	mask <<= left;
	mask >>= left + right;

	unsigned fVal = field[fPos[i]] >> right & mask;

	return fVal;
}

unsigned TBitFields::_get(int i) const
{
	unsigned mask = ~0;
	char left = fIndex[i] - fPos[i]*sizeof(unsigned)*8; // позиция слева от границы 4х байт
	char right = (fPos[i] + 1) * sizeof(unsigned) * 8 - fIndex[i] - fSizes[i]; // позиция справа от границы 4х байт

	mask <<= left;
	mask >>= left + right;

	unsigned fVal = field[fPos[i]] >> right & mask;

	return fVal;
}

int TBitFields::_findField(const Cmystring _fName) const
{
	for (int i = 0; i < fCount ; i++) 
		if (fNames[i] == _fName) 
			return i;
}

void TBitFields::SetField(const Cmystring _fName, unsigned fVals)
{
	int i = _findField(_fName);
	_copy(fVals, i);
}

unsigned TBitFields::GetField(const Cmystring _fName)
{
	int i = _findField(_fName);
	return _get(i);
}

unsigned TBitFields::GetField(const Cmystring _fName) const
{
	int i = _findField(_fName);
	return _get(i);
}

void TBitFields::AddField(const Cmystring _fName, unsigned fVals)
{
	int i = _findField(_fName);
	_copy(_get(i) + fVals,i);
}

ostream& operator<<(ostream& stream, const TBitFields& _bf)
{
	for (int i = 0; i < _bf.fCount; i++)
	{
		stream << _bf.fNames[i] << " = " << _bf._get(i) << endl;
	}
	return stream;
}

void TBitFields::see()
{	
	for (int y = 0; y < size; y++)
	{
		unsigned mask = 1 << 31;

		unsigned q = field[y];
	
		for (int i = 0; i < 32; i++) 
		{
			if (i % 8 == 0) cout << ' ';

			if (mask & q) cout << 1;
			else cout << 0;

			mask >>= 1;
		} 
		cout << endl;
	}
}