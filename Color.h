#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	char r, g, b, a;

	Color();
	Color(char r, char g, char b);
	Color(char r, char g, char b, char a);
	~Color();
};

#endif