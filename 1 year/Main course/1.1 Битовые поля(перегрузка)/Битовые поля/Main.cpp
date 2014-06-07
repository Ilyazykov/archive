#include <iostream>
#include "TBitFields.h"
using namespace std;

void main()
{
	Cmystring fnames[] =  { "a", "b", "c", "d", "e", "f", "g", "h" };
	char	  fsize[]  =  {  8,  16,   8,  16,  16,   8,   8,   8  };
	int fcount = 8;

	TBitFields bf(fcount, fnames, fsize);

	bf["a"] = 1;	cout << "a = " << bf["a"] << endl;
	bf["b"] = 2;	cout << "b = " << bf["b"] << endl;
	bf["c"] = 3;	cout << "c = " << bf["c"] << endl;
	bf["d"] = 4;	cout << "d = " << bf["d"] << endl;
	bf["e"] = 5;	cout << "e = " << bf["e"] << endl;
	bf["f"] = 6;	cout << "f = " << bf["f"] << endl;
	bf["g"] = 7; 	cout << "g = " << bf["g"] << endl;
	bf["h"] = 8; 	cout << "h = " << bf["h"] << endl;

	bf["h"] = bf["b"] + bf["c"];
	cout << "h = " << bf["h"] << endl;

	bf["g"] = bf["h"] = 6 + bf["c"] + 8 + bf["d"]; // 21
	cout << "h = " << bf["h"] << endl;
	cout << "g = " << bf["g"] << endl;

	bf["h"] = bf["a"] * (5 + bf["b"]) - (bf["d"] + bf["e"]) / bf["c"]; //1*(5+2)-(4+5)/3=4
	cout << "h = " << bf["h"] << endl;
	int rr;
	//rr = bf["h"];  // ошибка!!!!
	rr = bf["h"] + bf["e"]; //26


	//bf.see();

	cin.get();
}