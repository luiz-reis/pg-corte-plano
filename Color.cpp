#include "Color.h"

Color::Color() 
	: Color(0,0,0,255)
{
	
}

Color::Color(char r, char g, char b) 
	: Color(r, g, b, 255)
{
	
}

Color::Color(char r, char g, char b, char a) 
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::~Color()
{
	
}