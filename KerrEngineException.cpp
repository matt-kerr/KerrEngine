// Matthew Kerr

#include "KerrEngineException.h"

KerrEngineException::KerrEngineException(string code)
{
	cout << "KerrEngine error: " << code << endl;
}

KerrEngineException::~KerrEngineException() { }