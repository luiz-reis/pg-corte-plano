#include "Material.h"

Material::Material(float ka, float kd, float ks, float n, Vetor color)
{
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->n = n;
	this->od = color;
}

Material::~Material()
{
	
}

float Material::get_ka() const
{
	return this->ka;
}

float Material::get_kd() const
{
	return this->kd;
}

float Material::get_ks() const
{
	return this->ks;
}
	
float Material::get_n() const
{
	return this->n;
}

Vetor Material::get_od() const
{
	return this->od;
}

void Material::set_color(Vetor color)
{
	this->od = color;
}