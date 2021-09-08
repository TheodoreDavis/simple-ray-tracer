#include <inc/v3.h>

///////////////////////////////////////////////////////////////
// Accessors
///////////////////////////////////////////////////////////////

float v3::operator[](int i) const {
    return v[i];
}

float& v3::operator[](int i) {
    return v[i];
}

///////////////////////////////////////////////////////////////
// Unary
///////////////////////////////////////////////////////////////

v3 v3::operator+() {
    return *this;
}

v3 v3::operator-() {
    return v3(-v[0], -v[1], -v[2]);
}

///////////////////////////////////////////////////////////////
// Assignments
///////////////////////////////////////////////////////////////

v3& v3::operator=(const v3& rhs) {
    v[0] = rhs.v[0];
    v[1] = rhs.v[1];
    v[2] = rhs.v[2];

    return *this;
}

v3& v3::operator+=(const v3& rhs) {
    v[0] += rhs.v[0];
    v[1] += rhs.v[1];
    v[2] += rhs.v[2];

    return *this;
}

v3& v3::operator-=(const v3& rhs) {
    v[0] -= rhs.v[0];
    v[1] -= rhs.v[1];
    v[2] -= rhs.v[2];

    return *this;
}

v3& v3::operator*=(const v3& rhs) {
    v[0] *= rhs.v[0];
    v[1] *= rhs.v[1];
    v[2] *= rhs.v[2];

    return *this;
}

v3& v3::operator/=(const v3& rhs) {
    v[0] /= rhs.v[0];
    v[1] /= rhs.v[1];
    v[2] /= rhs.v[2];

    return *this;
}

v3& v3::operator*=(const float rhs) {
    v[0] *= rhs;
    v[1] *= rhs;
    v[2] *= rhs;

    return *this;
}

v3& v3::operator/=(const float rhs) {
    v[0] /= rhs;
    v[1] /= rhs;
    v[2] /= rhs;

    return *this;
}

///////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////

v3 v3::operator+(const v3& rhs) {
    return v3(v[0] + rhs.v[0], v[1] + rhs.v[1], v[2] + rhs.v[2]);
}

v3 v3::operator-(const v3& rhs) {
    return v3(v[0] - rhs.v[0], v[1] - rhs.v[1], v[2] - rhs.v[2]);
}

v3 v3::operator*(const v3& rhs) {
    return v3(v[0] * rhs.v[0], v[1] * rhs.v[1], v[2] * rhs.v[2]);
}

v3 v3::operator/(const v3& rhs) {
    return v3(v[0] / rhs.v[0], v[1] / rhs.v[1], v[2] / rhs.v[2]);
}

v3 v3::operator*(const float rhs) {
    return v3(v[0] * rhs, v[1] * rhs, v[2] * rhs);
}

v3 v3::operator/(const float rhs) {
    return v3(v[0] / rhs, v[1] / rhs, v[2] / rhs);
}

///////////////////////////////////////////////////////////////
// IO
///////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& out, const v3& rhs) {
    out << "{" << rhs.v[0] << "," << rhs.v[1] << "," << rhs.v[2] << "}";
    return out;
}

std::istream& operator<<(std::istream& in, const v3& rhs) {
    //TODO
}
