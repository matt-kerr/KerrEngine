// Matthew Kerr

#include <iostream>
#include "KerrEngineException.h"
using namespace std;

KerrEngineException::KerrEngineException(string code)
{
	cout << "KerrEngine error: " << code << endl;
}

KerrEngineException::~KerrEngineException() { }