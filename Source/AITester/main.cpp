#include <iostream>

#include "AILib.h"

using std::cout;
using std::cin;
using std::endl;

void OnExit();

int main()
{
	atexit(&OnExit);

	cout << "Hello world!" << endl;


	return 0;
}


void OnExit()
{
	cin.get();
}