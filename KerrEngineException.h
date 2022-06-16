// Matthew Kerr

#ifndef KERRENGINEEXCEPTION_H
#define KERRENGINEEXCEPTION_H

#include <fstream>
#include <string>
using namespace std;

class KerrEngineException
{
public:
	KerrEngineException(string code);
	virtual ~KerrEngineException();
};

#endif
