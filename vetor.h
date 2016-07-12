#ifndef VETOR_H
#define VETOR_H

#include <iostream>
#include <cfloat>

class Vetor
{
public:
	float x, y, z;
	Vetor();
	Vetor(float x, float y, float z);
	
	float norma() const;
	void m_escalar(const float escalar);
	void normalizar();
	
	static float p_escalar(const Vetor& v1, const Vetor& v2);
	static Vetor m_escalar(const Vetor& vetor, const float escalar);
	static Vetor normalizar(const Vetor& vetor);
	static bool colinear(Vetor& a, Vetor& b, Vetor& c);
	static Vetor intersect_segment(Vetor& n, Vetor& v0, Vetor& p0, Vetor& p1);
	static Vetor get_abg(const Vetor& p, const Vetor& p1, const Vetor& p2, const Vetor& p3);
	
	static const Vetor null;
	
	friend bool operator!=(const Vetor& lhs, const Vetor& rhs);
	friend bool operator==(const Vetor& lhs, const Vetor& rhs);
	
	friend Vetor operator+(Vetor lhs, const Vetor& rhs);
	Vetor& operator+=(const Vetor& rhs);
	
	friend Vetor operator-(const Vetor &lhs);
	
	friend Vetor operator-(Vetor lhs, const Vetor& rhs);
	Vetor& operator-=(const Vetor& rhs);
	
	friend Vetor operator*(Vetor lhs, const Vetor& rhs); // produto vetorial
	Vetor& operator*=(const Vetor& rhs);
	
	friend std::ostream& operator<< (std::ostream& out, const Vetor& vetor);
};

#endif
