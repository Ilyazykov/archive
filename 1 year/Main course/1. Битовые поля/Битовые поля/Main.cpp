#include <iostream>
#include "TBitFields.h"
using namespace std;

void main()
{
	unsigned u1, u2, u3, u4;
	Cmystring fnames[] =  { "a", "b", "c", "d", "e", "f", "g", "h" };
	char	  fsize[]  =  {  8,  16,   8,  16,  16,   8,   8,   8  };
	int fcount = 8;

	TBitFields bf(fcount, fnames, fsize);

	bf.SetField("a", 1);	cout << "a = " << bf.GetField("a") << endl;
	bf.SetField("b", 2);  	cout << "b = " << bf.GetField("b") << endl;
	bf.SetField("c", 3);	cout << "c = " << bf.GetField("c") << endl;
	bf.SetField("d", 4);	cout << "d = " << bf.GetField("d") << endl;
	bf.SetField("e", 5);	cout << "e = " << bf.GetField("e") << endl;
	bf.SetField("f", 6);	cout << "f = " << bf.GetField("f") << endl;
	bf.SetField("g", 7); 	cout << "g = " << bf.GetField("g") << endl;
	bf.SetField("h", 8); 	cout << "h = " << bf.GetField("h") << endl;
	
	bf.AddField("b", 8);
	cout << "b = " << bf.GetField("b") << endl;
	bf.AddField("c", bf.GetField("d"));
	cout << "c = " << bf.GetField("c") << endl;

	//cout << endl << bf;
	//bf.see();

	cin.get();
}