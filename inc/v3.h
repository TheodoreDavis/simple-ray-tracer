#include <inc/cmpfloat.h>
#include <iostream>
#include <cmath>

// Vector class with 3 components with common operations
class v3 {
    private:
        float v[3];
    
    public:
        // Constructors
        v3(float x, float y, float z) {v[0]=x, v[1]=y, v[2]=z;}

        // Accessors
        float operator[](int i) const;
        float& operator[](int i);

        // Unary
        v3 operator+();
        v3 operator-();

        // Assignments
        v3& operator=(const v3& rhs);
        v3& operator+=(const v3& rhs);
        v3& operator-=(const v3& rhs);
        v3& operator*=(const v3& rhs);
        v3& operator/=(const v3& rhs);
        v3& operator*=(const float rhs);
        v3& operator/=(const float rhs);

        // Operations
        v3 operator+(const v3& rhs);
        v3 operator-(const v3& rhs);
        v3 operator*(const v3& rhs);
        v3 operator/(const v3& rhs);
        v3 operator*(const float rhs);
        v3 operator/(const float rhs);
        friend v3 operator*(const float lhs, const v3& rhs);

        // Comparisons
        bool operator==(const v3& rhs);
        bool operator!=(const v3& rhs);
        bool operator>=(const v3& rhs); // Following comparisons look at magnitude
        bool operator<=(const v3& rhs); // Redundant code to speed up calculation times
        bool operator>(const v3& rhs);
        bool operator<(const v3& rhs);

        // IO
        friend std::ostream& operator<<(std::ostream& out, const v3& rhs);
        friend std::istream& operator>>(std::istream& in, const v3& rhs);

        // Vector Operations
        v3 crossProduct(const v3& rhs); // https://www.mathsisfun.com/algebra/vectors-cross-product.html
        float dotProduct(const v3& rhs); // https://www.mathsisfun.com/algebra/vectors-dot-product.html
        float magnitude();
        float magnitudeSquared();
        v3 unitVector();
        v3& normalize(); //TODO? convert *this to a unit vector

        // math
        friend float sqrt(float x);
};
