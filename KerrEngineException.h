// Matthew Kerr

#ifndef KERRENGINEEXCEPTION_H
#define KERRENGINEEXCEPTION_H

#include <iostream>
#include <string>
using namespace std;

class KerrEngineException
{
public:
	KerrEngineException(std::string code);
	virtual ~KerrEngineException();
};

#endif
