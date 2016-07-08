#ifndef MATRIX4_H
#define MATRIX4_H

struct vec4
{
    float values[4];
    vec4();
    vec4(float x, float y, float z, float w);
    const float& operator[] ( int index ) const;
    float& operator[] ( int index );
};

class Matrix4
{		
public:
    vec4 columns[4];
	
    Matrix4();
    Matrix4(vec4 x, vec4 y, vec4 z, vec4 w);
	
	const vec4& operator[](int index) const;
	vec4& operator[](int index);
	
	friend Matrix4 operator*(Matrix4 m1, const Matrix4& m2);
	friend vec4 operator*(const Matrix4& m, const vec4& v);
	friend vec4 operator*(const vec4& v, const Matrix4& m);
};

#endif