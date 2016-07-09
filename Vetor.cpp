#include "Vetor.h"
#include <cmath>

Vetor::Vetor()
{
	this->x = this->y = this->z = 0;
}

Vetor::Vetor(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vetor::norma() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vetor::m_escalar(float escalar)
{
	this->x *= escalar;
	this->y *= escalar;
	this->z *= escalar;
}

void Vetor::normalizar()
{
	m_escalar(1.0f/norma());
}

Vetor Vetor::m_escalar(const Vetor& vetor, const float escalar)
{
	Vetor ret = vetor;
	ret.m_escalar(escalar);
	
	return ret;
}

Vetor Vetor::normalizar(const Vetor& vetor)
{
	Vetor ret = vetor;
	ret.normalizar();
	
	return ret;
}

float Vetor::p_escalar(const Vetor& v1, const Vetor& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vetor& Vetor::operator+=(const Vetor& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	
	return *this;
}

Vetor operator+(Vetor lhs, const Vetor& rhs)
{
	lhs += rhs;
	return lhs;
}

Vetor operator-(const Vetor &lhs)
{
	return Vetor::m_escalar(lhs, -1);
}

Vetor& Vetor::operator-=(const Vetor& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
		
	return *this;
}

Vetor operator-(Vetor lhs, const Vetor& rhs)
{
	lhs -= rhs;
	return lhs;
}

Vetor& Vetor::operator*=(const Vetor& rhs)
{
//	a × b = [a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1].
	float x = this->y * rhs.z - this->z * rhs.y;
	float y = this->z * rhs.x - this->x * rhs.z;
	float z = this->x * rhs.y - this->y * rhs.x;
	
	this->x = x;
	this->y = y;
	this->z = z;
	
	return *this;
}

Vetor operator*(Vetor lhs, const Vetor& rhs)
{
	lhs *= rhs;
	return lhs;
}

std::ostream& operator<< (std::ostream& out, const Vetor& vetor)
{
	out << "{ " << vetor.x << ", " << vetor.y << ", " << vetor.z << " }";
	return out;
}
