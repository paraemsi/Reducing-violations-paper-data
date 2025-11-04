#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_alias real_val, float_alias imag_val)
    : real_part(real_val), imag_part(imag_val) {}

float_alias Complex::real() const {
    return real_part;
}

float_alias Complex::imag() const {
    return imag_part;
}

Complex Complex::operator+(const Complex& rhs) const {
    return Complex((real_part + rhs.real_part), (imag_part + rhs.imag_part));
}

Complex Complex::operator-(const Complex& rhs) const {
    return Complex((real_part - rhs.real_part), (imag_part - rhs.imag_part));
}

Complex Complex::operator*(const Complex& rhs) const {
    // (a + i*b) * (c + i*d) = (a*c - b*d) + (b*c + a*d)*i
    float_alias a = real_part;
    float_alias b = imag_part;
    float_alias c = rhs.real_part;
    float_alias d = rhs.imag_part;
    float_alias real_res = ((a * c) - (b * d));
    float_alias imag_res = ((b * c) + (a * d));
    return Complex(real_res, imag_res);
}

Complex Complex::operator/(const Complex& rhs) const {
    // (a + i*b) / (c + i*d) = ((a*c + b*d)/(c^2 + d^2)) + ((b*c - a*d)/(c^2 + d^2))*i
    float_alias a = real_part;
    float_alias b = imag_part;
    float_alias c = rhs.real_part;
    float_alias d = rhs.imag_part;
    float_alias denom = ((c * c) + (d * d));
    float_alias real_res = (((a * c) + (b * d)) / denom);
    float_alias imag_res = (((b * c) - (a * d)) / denom);
    return Complex(real_res, imag_res);
}

Complex Complex::operator+(float_alias rhs) const {
    // (a + bi) + r = (a + r) + bi
    return Complex((real_part + rhs), imag_part);
}

Complex Complex::operator-(float_alias rhs) const {
    // (a + bi) - r = (a - r) + bi
    return Complex((real_part - rhs), imag_part);
}

Complex Complex::operator*(float_alias rhs) const {
    // (a + bi) * r = (a*r) + (b*r)i
    return Complex((real_part * rhs), (imag_part * rhs));
}

Complex Complex::operator/(float_alias rhs) const {
    // (a + bi) / r = (a/r) + (b/r)i
    return Complex((real_part / rhs), (imag_part / rhs));
}

Complex operator+(float_alias lhs, const Complex& rhs) {
    // r + (a + bi) = (r + a) + bi
    return Complex((lhs + rhs.real_part), rhs.imag_part);
}

Complex operator-(float_alias lhs, const Complex& rhs) {
    // r - (a + bi) = (r - a) - bi
    return Complex((lhs - rhs.real_part), (-rhs.imag_part));
}

Complex operator*(float_alias lhs, const Complex& rhs) {
    // r * (a + bi) = (r*a) + (r*b)i
    return Complex((lhs * rhs.real_part), (lhs * rhs.imag_part));
}

Complex operator/(float_alias lhs, const Complex& rhs) {
    // r / (a + bi) = (r * (a - bi)) / (a^2 + b^2)
    float_alias denom = ((rhs.real_part * rhs.real_part) + (rhs.imag_part * rhs.imag_part));
    float_alias real_res = ((lhs * rhs.real_part) / denom);
    float_alias imag_res = ((-lhs * rhs.imag_part) / denom);
    return Complex(real_res, imag_res);
}

Complex Complex::conj() const {
    return Complex(real_part, (-imag_part));
}

float_alias Complex::abs() const {
    // sqrt(a^2 + b^2)
    return std::sqrt(((real_part * real_part) + (imag_part * imag_part)));
}

Complex Complex::exp() const {
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    float_alias exp_a = std::exp(real_part);
    float_alias cos_b = std::cos(imag_part);
    float_alias sin_b = std::sin(imag_part);
    return Complex((exp_a * cos_b), (exp_a * sin_b));
}

}  // namespace complex_numbers
