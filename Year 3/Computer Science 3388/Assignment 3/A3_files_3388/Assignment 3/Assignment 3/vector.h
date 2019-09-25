#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

// A generalized 2-dimensional vector.
class Vector2D
{
public:
    // Default constructor
    inline Vector2D() { vec[0] = vec[1] = 0.0; }
    // Construct from fwo floats
    inline Vector2D(float x, float y) { vec[0] = x; vec[1] = y; }
    // Copy constructor
    inline Vector2D(const Vector2D& v) { vec[0] = v.vec[0]; vec[1] = v.vec[1]; }

    // Assignment operator
    inline Vector2D& operator=(const Vector2D& v) 
    { vec[0] = v.vec[0]; vec[1] = v.vec[1]; return *this; }

    // Element access
    inline float& operator[](int i) { return vec[i]; }
    inline const float& operator[](int i) const { return vec[i]; }

    // Cast operator to float array
    inline operator float*() { return vec; }

    // Comparison operators
    inline bool operator==(const Vector2D& v) const
    { return vec[0] == v.vec[0] && vec[1] == v.vec[1]; }
    inline bool operator!=(const Vector2D& v) const
    { return !(*this == v); }

    //
    // Arithmetic operators
    //

    // Vector-vector addition/subtraction
    inline Vector2D operator+(const Vector2D& v) const
    { return Vector2D(vec[0]+v.vec[0], vec[1]+v.vec[1]); }
    inline Vector2D operator-(const Vector2D& v) const
    { return Vector2D(vec[0]-v.vec[0], vec[1]-v.vec[1]); }
    inline Vector2D& operator+=(const Vector2D& v)
    { vec[0] += v.vec[0]; vec[1] += v.vec[1]; return *this; }
    inline Vector2D& operator-=(const Vector2D& v)
    { vec[0] -= v.vec[0]; vec[1] -= v.vec[1]; return *this; }

    // Vector-scalar multiplication/division
    inline Vector2D operator*(float a) const
    { return Vector2D(vec[0]*a, vec[1]*a); }
    inline Vector2D operator/(float a) const
    { float inv_a = 1.0f/a; return Vector2D(vec[0]*inv_a, vec[1]*inv_a); }
    inline Vector2D& operator*=(float a)
    { vec[0] *= a; vec[1] *= a; return *this; }
    inline Vector2D& operator/=(float a)
    { float inv_a = 1.0f/a; vec[0] *= inv_a; vec[1] *= inv_a; return *this; }

    // Normalization operations
    inline float norm2() const { return vec[0]*vec[0] + vec[1]*vec[1]; }
    inline float norm() const { return sqrt(norm2()); }
    inline float length() const { return norm(); }
    inline Vector2D& normalize()
    {
        float h = norm();
        if (h != 0.0)
        {
            h = 1.0f/h;
            vec[0] *= h; vec[1] *= h;
        }
        return *this;
    }

    // Dot product
    inline float dot(const Vector2D& v) const 
    { return vec[0]*v.vec[0] + vec[1]*v.vec[1]; }

private:
    float vec[2];
};


// Free scalar-vector multiplication operator
static inline Vector2D operator*(float a, const Vector2D& v)
{ return Vector2D(v[0]*a, v[1]*a); }


#endif
