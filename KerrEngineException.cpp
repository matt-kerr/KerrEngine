#include <iostream>
#include "KerrEngineException.h"
using namespace std;

KerrEngineException::KerrEngineException()
{
	cout << "Unspecified error in KerrEngineException" << endl;
}

KerrEngineException::KerrEngineException(string code)
{
	cout << "KerrEngine error: " << code << endl;
}

KerrEngineException::~KerrEngineException()
{

}