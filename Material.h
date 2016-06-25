#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material
{
private:
	float ka, kd, ks;
	unsigned float n;
	Color od;
public:
	Material(float ka, float kd, float ks, unsigned float n, Color od);
	~Material();
	
	float get_ka() const;
	float get_kd() const;
	float get_ks() const;
	unsigned float get_n() const;
	Color get_od() const;
	
	void set_color(Color color);
};

#endif