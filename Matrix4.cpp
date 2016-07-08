#include "Matrix4.h"

vec4::vec4() 
{
    values[0] = values[1] = values[2] = values[3] = 0;
}

vec4::vec4(float x, float y, float z, float w)
{
    values[0] = x;
    values[1] = y;
    values[2] = z;
    values[3] = w;
}

// Provide array-like index operators for the vector components.
const float& vec4::operator[] (int index) const
{
    return values[index];
}
float& vec4::operator[] (int index)
{
    return values[index];
}
  
Matrix4::Matrix4()
{
    columns[0] = vec4( 1, 0, 0, 0 );
    columns[1] = vec4( 0, 1, 0, 0 );
    columns[2] = vec4( 0, 0, 1, 0 );
    columns[3] = vec4( 0, 0, 0, 1 );
}

Matrix4::Matrix4(vec4 x, vec4 y, vec4 z, vec4 w)
{
    columns[0] = x;
    columns[1] = y;
    columns[2] = z;
    columns[3] = w;
}

// Provide array-like index operators for the columns of the matrix.
const vec4& Matrix4::operator[](int index) const
{
    return columns[index];
}

vec4& Matrix4::operator[](int index)
{
    return columns[index];
}

Matrix4 operator*(Matrix4 m1, const Matrix4& m2)
{
	vec4 X = m1 * m2[0];
	vec4 Y = m1 * m2[1];
	vec4 Z = m1 * m2[2];
	vec4 W = m1 * m2[3];
 
	return Matrix4(X, Y, Z, W);
}

vec4 operator*(const Matrix4& m, const vec4& v)
{
    return vec4( 
           m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
           m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
           m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
           m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
       );
}

vec4 operator*(const vec4& v, const Matrix4& m)
{
	return vec4(
	        v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3],
	        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3],
	        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3],
	        v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]
	    );
}
