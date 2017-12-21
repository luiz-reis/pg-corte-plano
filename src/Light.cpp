#include "Light.h"

Light::Light(Vetor pos, float ip, Color color)
{
	this->pos = pos;
	this->ip = ip;
	this->color = color;
}

Light::~Light()
{
	
}

Vetor Light::get_pos() const
{
	return this->pos;
}

Color Light::get_color() const
{
	return this->color;
}

float Light::get_ip() const
{
	return this->ip;
}

void Light::set_ip(float ip)
{
	this->ip = ip;
}

void Light::set_color(Color color)
{
	this->color = color;
}

void Light::set_pos(Vetor pos)
{
	this->pos = pos;
}