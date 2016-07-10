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