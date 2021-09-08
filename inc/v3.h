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

        //operations
        v3 operator+(const v3& rhs);
        v3 operator-(const v3& rhs);
        v3 operator*(const v3& rhs);
        v3 operator/(const v3& rhs);
        v3 operator*(const float rhs);
        v3 operator/(const float rhs);

        // Vector Operations

        // IO
        friend std::ostream& operator<<(std::ostream& out, const v3& rhs);
        friend std::istream& operator<<(std::istream& in, const v3& rhs);
};
