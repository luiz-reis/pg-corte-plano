#include "Vetor.h"
#include <cmath>

const Vetor Vetor::null = Vetor(FLT_MAX, FLT_MAX, FLT_MAX);

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
	float n = norma();
	if(n == 0)
		return;
	
	m_escalar(1.0f/n);
}

bool Vetor::colinear(Vetor& a, Vetor& b, Vetor& c)
{
	return a.x * b.y + a.y * c.x + b.x * c.y - (c.x * b.y + a.x * c.y + b.x * a.y) == 0;
}

Vetor Vetor::intersect_segment(Vetor& n, Vetor& v0, Vetor& p0, Vetor& p1)
{
	float num, den, r;
	den = Vetor::p_escalar(n, p1 - p0);
	if(den != 0){
		num = Vetor::p_escalar(n, v0 - p0);
		r = num / den;
		if(r >= 0 && r <= 1) {
			return p0 + Vetor::m_escalar(p1 - p0, r);
		}
	}
	
	return Vetor::null;
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

bool operator!=(const Vetor& lhs, const Vetor& rhs)
{
	return !(lhs == rhs);
}
	
bool operator==(const Vetor& lhs, const Vetor& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
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
