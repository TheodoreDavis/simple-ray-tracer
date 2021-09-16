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

float v3::x() const {
    return v[0];
}

float& v3::x() {
    return v[0];
}

float v3::y() const {
    return v[1];
}

float& v3::y() {
    return v[1];
}

float v3::z() const {
    return v[2];
}

float& v3::z() {
    return v[2];
}

float v3::r() const {
    return v[0];
}

float& v3::r() {
    return v[0];
}

float v3::g() const {
    return v[1];
}

float& v3::g() {
    return v[1];
}

float v3::b() const {
    return v[2];
}

float& v3::b() {
    return v[2];
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

v3 const v3::operator+(const v3& rhs) {
    return v3(v[0] + rhs.v[0], v[1] + rhs.v[1], v[2] + rhs.v[2]);
}

v3 const v3::operator-(const v3& rhs) {
    return v3(v[0] - rhs.v[0], v[1] - rhs.v[1], v[2] - rhs.v[2]);
}

v3 const v3::operator*(const v3& rhs) {
    return v3(v[0] * rhs.v[0], v[1] * rhs.v[1], v[2] * rhs.v[2]);
}

v3 const v3::operator/(const v3& rhs) {
    return v3(v[0] / rhs.v[0], v[1] / rhs.v[1], v[2] / rhs.v[2]);
}

v3 const v3::operator*(const float rhs) {
    return v3(v[0] * rhs, v[1] * rhs, v[2] * rhs);
}

v3 const v3::operator/(const float rhs) {
    return v3(v[0] / rhs, v[1] / rhs, v[2] / rhs);
}

v3 const operator*(const float lhs, const v3& rhs) {
    return v3(rhs.v[0] * lhs, rhs.v[1] * lhs, rhs.v[2] * lhs);
}

///////////////////////////////////////////////////////////////
// Comparisons
///////////////////////////////////////////////////////////////

bool v3::operator==(const v3& rhs) {
    return (CMPFLOAT_EQUAL(v[0], rhs.v[0]) &&
            CMPFLOAT_EQUAL(v[1], rhs.v[1]) &&
            CMPFLOAT_EQUAL(v[2], rhs.v[2]));
}

bool v3::operator!=(const v3& rhs) {
    return (CMPFLOAT_NEQUAL(v[0], rhs.v[0]) ||
            CMPFLOAT_NEQUAL(v[1], rhs.v[1]) ||
            CMPFLOAT_NEQUAL(v[2], rhs.v[2]));
}

bool v3::operator>=(const v3& rhs) {
    return CMPFLOAT_EGREATER(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

bool v3::operator<=(const v3& rhs) {
    return CMPFLOAT_ELESS(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

bool v3::operator>(const v3& rhs) {
    return CMPFLOAT_GREATER(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

bool v3::operator<(const v3& rhs) {
    return CMPFLOAT_LESS(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

///////////////////////////////////////////////////////////////
// IO
///////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& out, const v3& rhs) {
    out << "{" << rhs.v[0] << "," << rhs.v[1] << "," << rhs.v[2] << "}";
    return out;
}

//std::istream& operator<<(std::istream& in, const v3& rhs) {
//    //TODO
//}

///////////////////////////////////////////////////////////////
// Vector Operations
///////////////////////////////////////////////////////////////

v3 const v3::crossProduct(const v3& rhs) {
    return v3(v[1] * rhs.v[2] - v[2] * rhs.v[1],
              v[2] * rhs.v[0] - v[0] * rhs.v[2],
              v[0] * rhs.v[1] - v[1] * rhs.v[0]);
}

float const v3::dotProduct(const v3& rhs) {
    return v[0] * rhs.v[0] + v[1] * rhs.v[1] + v[2] * rhs.v[2];
}

float const v3::magnitude() {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float const v3::magnitudeSquared() {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

float const v3::distance(const v3& rhs) {
    return sqrt((v[0] - rhs.v[0]) * (v[0] - rhs.v[0]) +
                (v[1] - rhs.v[1]) * (v[1] - rhs.v[1]) +
                (v[2] - rhs.v[2]) * (v[2] - rhs.v[2]));
}

float const v3::distanceSquared(const v3& rhs) {
    return (v[0] - rhs.v[0]) * (v[0] - rhs.v[0]) +
           (v[1] - rhs.v[1]) * (v[1] - rhs.v[1]) +
           (v[2] - rhs.v[2]) * (v[2] - rhs.v[2]);
}

v3 const v3::unitVector() {
    float m = this->magnitude();
    return v3(v[0] / m, v[1] / m, v[2] / m);
}

v3& v3::normalize() {
    float m = this->magnitude();
    v[0] /= m;
    v[1] /= m;
    v[2] /= m;

    return *this;
}
