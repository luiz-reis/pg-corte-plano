#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vetor.h"

class Material
{
private:
	float ka, kd, ks;
	float n;
	Vetor od;
public:
	Material(float ka, float kd, float ks, float n, Vetor od);
	~Material();
	
	float get_ka() const;
	float get_kd() const;
	float get_ks() const;
	float get_n() const;
	Vetor get_od() const;
	
	void set_color(Vetor color);
};

#endif