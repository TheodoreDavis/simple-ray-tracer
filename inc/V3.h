#ifndef _V3_
#define _V3_

#include <iostream>
#include <cmath>

#include <inc/floatutils.h>

// Vector class with 3 components with common operations
class V3 {
    private:
        float v[3];

    public:
        // Constructors
        V3() {}
        V3(float x, float y, float z) {v[0]=x, v[1]=y, v[2]=z;}
        V3(const V3& rhs) {v[0]=rhs.v[0], v[1]=rhs.v[1], v[2]=rhs.v[2];}

        // Accessors
        float operator[](int i) const;
        float& operator[](int i);
        float x() const;
        float& x();
        float y() const;
        float& y();
        float z() const;
        float& z();
        float r() const;
        float& r();
        float g() const;
        float& g();
        float b() const;
        float& b();


        // Unary
        V3 operator+() const;
        V3 operator-() const;

        // Assignments
        V3& operator=(const V3& rhs);
        V3& operator+=(const V3& rhs);
        V3& operator-=(const V3& rhs);
        V3& operator*=(const V3& rhs);
        V3& operator/=(const V3& rhs);
        V3& operator*=(const float rhs);
        V3& operator/=(const float rhs);

        // Operations
        V3 operator+(const V3& rhs) const;
        V3 operator-(const V3& rhs) const;
        V3 operator*(const V3& rhs) const;
        V3 operator/(const V3& rhs) const;
        V3 operator*(const float rhs) const;
        V3 operator/(const float rhs) const;
        friend V3 const operator*(const float lhs, const V3& rhs);

        // Comparisons
        bool operator==(const V3& rhs);
        bool operator!=(const V3& rhs);
        bool operator>=(const V3& rhs); // Following comparisons look at magnitude
        bool operator<=(const V3& rhs); // Redundant code to speed up calculation times
        bool operator>(const V3& rhs);
        bool operator<(const V3& rhs);

        // IO
        friend std::ostream& operator<<(std::ostream& out, const V3& rhs);
        friend std::istream& operator>>(std::istream& in, const V3& rhs);

        // Vector Operations
        V3 const crossProduct(const V3& rhs) const; // https://www.mathsisfun.com/algebra/vectors-cross-product.html
        float const dotProduct(const V3& rhs) const; // https://www.mathsisfun.com/algebra/vectors-dot-product.html
        float const magnitude() const;
        float const magnitudeSquared() const;
        float const distance(const V3& rhs) const;
        float const distanceSquared(const V3& rhs) const;
        V3 const unitVector() const;
        V3& normalize(); //TODO? convert *this to a unit vector

        // math
        friend float sqrt(float x);
};
#endif
