#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	int r, g, b, a;

	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	~Color();
	
	friend Color operator+(Color lhs, const Color& rhs);
	Color& operator+=(const Color& rhs);
};

#endif