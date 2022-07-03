// Matthew Kerr

#ifndef PATTERN_H
#define PATTERN_H

#include "Color.h"
#include "Matrix.h"
#include "KerrEngineException.h"

class Pattern
{
	public:
		Color a;
		Color b;
		string type;
		Matrix transform;

		// constructors
		Pattern();
		virtual ~Pattern();
		Pattern(const Color& a, const Color& b, const string& type);
		Pattern(const Color& a, const Color& b, const string& type, const Matrix& transform);

		Pattern(const Pattern& orig); // copy constructor
		Pattern(Pattern&& orig) noexcept; // move constructor

		// operator overloads
		Pattern& operator=(const Pattern& rhs); // = operator overload
		Pattern& operator=(Pattern&& orig); // move = operator overload (move assignment overload)
		bool operator==(const Pattern& rhs); // == operator overload		
};

#endif