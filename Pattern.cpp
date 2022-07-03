// Matthew Kerr

#include "Pattern.h"

using namespace std;

Pattern::Pattern()
{
	this->a = Color(0.0, 0.0, 0.0);
	this->b = Color(0.0, 0.0, 0.0);
	this->type = "none";
	this->transform = Matrix::identity(4);
}

Pattern::~Pattern() { }

Pattern::Pattern(const Color& a, const Color& b, const string& type)
{
	this->a = a;
	this->b = b;
	this->type = type;
	this->transform = Matrix::identity(4);
}

Pattern::Pattern(const Color& a, const Color& b, const string& type, const Matrix& transform)
{
	this->a = a;
	this->b = b;
	this->type = type;
	this->transform = transform;
}

// copy constructor
Pattern::Pattern(const Pattern& orig)
{
	this->a = orig.a;
	this->b = orig.b;
	this->type = orig.type;
	this->transform = orig.transform;
}

// move constructor
Pattern::Pattern(Pattern&& orig) noexcept
{
	this->a = orig.a;
	this->b = orig.b;
	this->type = orig.type;
	this->transform = orig.transform;
}

// = operator overload
Pattern& Pattern::operator=(const Pattern& rhs)
{
	this->a = rhs.a;
	this->b = rhs.b;
	this->type = rhs.type;
	this->transform = rhs.transform;
	return *this;
}

// move = operator overload (move assignment overload)
Pattern& Pattern::operator=(Pattern&& orig)
{
	if (this != &orig)
	{
		this->a = orig.a;
		this->b = orig.b;
		this->type = orig.type;
		this->transform = orig.transform;
	}
	return *this;
}

// == operator overload
bool Pattern::operator==(const Pattern& rhs)
{
	return (this->a == rhs.a) && (this->b == rhs.b) && (this->type == rhs.type) && (this->transform == transform);
}