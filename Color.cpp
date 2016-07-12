#include "Color.h"

Color::Color() 
	: Color(0,0,0,255)
{
	
}

Color::Color(int r, int g, int b) 
	: Color(r, g, b, 255)
{
	
}

Color::Color(int r, int g, int b, int a) 
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::~Color()
{
	
}

Color& Color::operator+=(const Color& rhs)
{
	this->r += rhs.r;
	this->g += rhs.g;
	this->b += rhs.b;
	
	return *this;
}

Color operator+(Color lhs, const Color& rhs)
{
	lhs += rhs;
	return lhs;
}