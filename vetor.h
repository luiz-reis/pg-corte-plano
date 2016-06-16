#ifndef VETOR_H
#define VETOR_H

#include <iostream>

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
	
	friend Vetor operator+(Vetor lhs, const Vetor& rhs);
	Vetor& operator+=(const Vetor& rhs);
	
	friend Vetor operator*(Vetor lhs, const Vetor& rhs); // produto vetorial
	Vetor& operator*=(const Vetor& rhs);
	
	friend std::ostream& operator<< (std::ostream& out, const Vetor& vetor);
};

#endif
