#include <inc/V3.h>

///////////////////////////////////////////////////////////////
// Accessors
///////////////////////////////////////////////////////////////

float V3::operator[](int i) const {
    return v[i];
}

float& V3::operator[](int i) {
    return v[i];
}

float V3::x() const {
    return v[0];
}

float& V3::x() {
    return v[0];
}

float V3::y() const {
    return v[1];
}

float& V3::y() {
    return v[1];
}

float V3::z() const {
    return v[2];
}

float& V3::z() {
    return v[2];
}

float V3::r() const {
    return v[0];
}

float& V3::r() {
    return v[0];
}

float V3::g() const {
    return v[1];
}

float& V3::g() {
    return v[1];
}

float V3::b() const {
    return v[2];
}

float& V3::b() {
    return v[2];
}

///////////////////////////////////////////////////////////////
// Unary
///////////////////////////////////////////////////////////////

V3 V3::operator+() const {
    return *this;
}

V3 V3::operator-() const {
    return V3(-v[0], -v[1], -v[2]);
}

///////////////////////////////////////////////////////////////
// Assignments
///////////////////////////////////////////////////////////////

V3& V3::operator=(const V3& rhs) {
    v[0] = rhs.v[0];
    v[1] = rhs.v[1];
    v[2] = rhs.v[2];

    return *this;
}

V3& V3::operator+=(const V3& rhs) {
    v[0] += rhs.v[0];
    v[1] += rhs.v[1];
    v[2] += rhs.v[2];

    return *this;
}

V3& V3::operator-=(const V3& rhs) {
    v[0] -= rhs.v[0];
    v[1] -= rhs.v[1];
    v[2] -= rhs.v[2];

    return *this;
}

V3& V3::operator*=(const V3& rhs) {
    v[0] *= rhs.v[0];
    v[1] *= rhs.v[1];
    v[2] *= rhs.v[2];

    return *this;
}

V3& V3::operator/=(const V3& rhs) {
    v[0] /= rhs.v[0];
    v[1] /= rhs.v[1];
    v[2] /= rhs.v[2];

    return *this;
}

V3& V3::operator*=(const float rhs) {
    v[0] *= rhs;
    v[1] *= rhs;
    v[2] *= rhs;

    return *this;
}

V3& V3::operator/=(const float rhs) {
    v[0] /= rhs;
    v[1] /= rhs;
    v[2] /= rhs;

    return *this;
}

///////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////

V3 V3::operator+(const V3& rhs) const {
    return V3(v[0] + rhs.v[0], v[1] + rhs.v[1], v[2] + rhs.v[2]);
}

V3 V3::operator-(const V3& rhs) const {
    return V3(v[0] - rhs.v[0], v[1] - rhs.v[1], v[2] - rhs.v[2]);
}

V3 V3::operator*(const V3& rhs) const {
    return V3(v[0] * rhs.v[0], v[1] * rhs.v[1], v[2] * rhs.v[2]);
}

V3 V3::operator/(const V3& rhs) const {
    return V3(v[0] / rhs.v[0], v[1] / rhs.v[1], v[2] / rhs.v[2]);
}

V3 V3::operator*(const float rhs) const {
    return V3(v[0] * rhs, v[1] * rhs, v[2] * rhs);
}

V3 V3::operator/(const float rhs) const {
    return V3(v[0] / rhs, v[1] / rhs, v[2] / rhs);
}

V3 const operator*(const float lhs, const V3& rhs) {
    return V3(rhs.v[0] * lhs, rhs.v[1] * lhs, rhs.v[2] * lhs);
}

///////////////////////////////////////////////////////////////
// Comparisons
///////////////////////////////////////////////////////////////

bool V3::operator==(const V3& rhs) {
    return (FLOAT_EQUAL(v[0], rhs.v[0]) &&
            FLOAT_EQUAL(v[1], rhs.v[1]) &&
            FLOAT_EQUAL(v[2], rhs.v[2]));
}

bool V3::operator!=(const V3& rhs) {
    return (FLOAT_NEQUAL(v[0], rhs.v[0]) ||
            FLOAT_NEQUAL(v[1], rhs.v[1]) ||
            FLOAT_NEQUAL(v[2], rhs.v[2]));
}

bool V3::operator>=(const V3& rhs) {
    return FLOAT_EGREATER(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

bool V3::operator<=(const V3& rhs) {
    return FLOAT_ELESS(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

bool V3::operator>(const V3& rhs) {
    return FLOAT_GREATER(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

bool V3::operator<(const V3& rhs) {
    return FLOAT_LESS(v[0] * v[0] + v[1] * v[1] + v[2] * v[2],
            rhs.v[0] * rhs.v[0] + rhs.v[1] * rhs.v[1] + rhs.v[2] * rhs.v[2]);
}

///////////////////////////////////////////////////////////////
// IO
///////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& out, const V3& rhs) {
    out << "{" << rhs.v[0] << "," << rhs.v[1] << "," << rhs.v[2] << "}";
    return out;
}

//std::istream& operator<<(std::istream& in, const V3& rhs) {
//    //TODO
//}

///////////////////////////////////////////////////////////////
// Vector Operations
///////////////////////////////////////////////////////////////

V3 const V3::crossProduct(const V3& rhs) const {
    return V3(v[1] * rhs.v[2] - v[2] * rhs.v[1],
              v[2] * rhs.v[0] - v[0] * rhs.v[2],
              v[0] * rhs.v[1] - v[1] * rhs.v[0]);
}

float const V3::dotProduct(const V3& rhs) const {
    return v[0] * rhs.v[0] + v[1] * rhs.v[1] + v[2] * rhs.v[2];
}

float const V3::magnitude() const {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float const V3::magnitudeSquared() const {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

float const V3::distance(const V3& rhs) const {
    return sqrt((v[0] - rhs.v[0]) * (v[0] - rhs.v[0]) +
                (v[1] - rhs.v[1]) * (v[1] - rhs.v[1]) +
                (v[2] - rhs.v[2]) * (v[2] - rhs.v[2]));
}

float const V3::distanceSquared(const V3& rhs) const {
    return (v[0] - rhs.v[0]) * (v[0] - rhs.v[0]) +
           (v[1] - rhs.v[1]) * (v[1] - rhs.v[1]) +
           (v[2] - rhs.v[2]) * (v[2] - rhs.v[2]);
}

V3 const V3::unitVector() const {
    float m = this->magnitude();
    return V3(v[0] / m, v[1] / m, v[2] / m);
}

V3& V3::normalize() {
    float m = this->magnitude();
    v[0] /= m;
    v[1] /= m;
    v[2] /= m;

    return *this;
}
