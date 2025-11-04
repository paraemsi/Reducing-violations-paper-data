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
    float_alias real_res = ((real_part * rhs.real_part) - (imag_part * rhs.imag_part));
    float_alias imag_res = ((imag_part * rhs.real_part) + (real_part * rhs.imag_part));
    return Complex(real_res, imag_res);
}

Complex Complex::operator/(const Complex& rhs) const {
    float_alias denom = ((rhs.real_part * rhs.real_part) + (rhs.imag_part * rhs.imag_part));
    float_alias real_res = (((real_part * rhs.real_part) + (imag_part * rhs.imag_part)) / denom);
    float_alias imag_res = (((imag_part * rhs.real_part) - (real_part * rhs.imag_part)) / denom);
    return Complex(real_res, imag_res);
}

Complex Complex::conj() const {
    return Complex(real_part, (-imag_part));
}

float_alias Complex::abs() const {
    return std::sqrt(((real_part * real_part) + (imag_part * imag_part)));
}

Complex Complex::exp() const {
    float_alias exp_real = std::exp(real_part);
    float_alias real_res = (exp_real * std::cos(imag_part));
    float_alias imag_res = (exp_real * std::sin(imag_part));
    return Complex(real_res, imag_res);
}

// Scalar overloads (member)
Complex Complex::operator+(float_alias rhs) const {
    return Complex((real_part + rhs), imag_part);
}
Complex Complex::operator-(float_alias rhs) const {
    return Complex((real_part - rhs), imag_part);
}
Complex Complex::operator*(float_alias rhs) const {
    return Complex((real_part * rhs), (imag_part * rhs));
}
Complex Complex::operator/(float_alias rhs) const {
    return Complex((real_part / rhs), (imag_part / rhs));
}

// Scalar overloads (friend, non-member)
Complex operator+(float_alias lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real_part), rhs.imag_part);
}
Complex operator-(float_alias lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real_part), (-rhs.imag_part));
}
Complex operator*(float_alias lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real_part), (lhs * rhs.imag_part));
}
Complex operator/(float_alias lhs, const Complex& rhs) {
    // (a) / (c + id) = (a * c)/(c^2 + d^2) + (-a * d)/(c^2 + d^2) * i
    float_alias denom = ((rhs.real_part * rhs.real_part) + (rhs.imag_part * rhs.imag_part));
    float_alias real_res = ((lhs * rhs.real_part) / denom);
    float_alias imag_res = ((-lhs * rhs.imag_part) / denom);
    return Complex(real_res, imag_res);
}

}  // namespace complex_numbers
