#ifndef LIGHT_H
#define LIGHT_H

#include "Vetor.h"
#include "Color.h"

class Light
{
private:
	Vetor pos;
	Color color;
	float ip;
public:
	Light(Vetor pos, float ip, Color color);
	~Light();
	
	Vetor get_pos() const;
	Color get_color() const;
	float get_ip() const;
	
	void set_ip(float ip);
	void set_color(Color color);
	void set_pos(Vetor pos);	
};

#endif