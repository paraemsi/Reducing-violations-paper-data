#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_alias real_value, float_alias imag_value)
    : real_part(real_value), imag_part(imag_value) {}

float_alias Complex::real() const {
    return real_part;
}

float_alias Complex::imag() const {
    return imag_part;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex((real_part + other.real_part), (imag_part + other.imag_part));
}

Complex Complex::operator-(const Complex& other) const {
    return Complex((real_part - other.real_part), (imag_part - other.imag_part));
}

Complex Complex::operator*(const Complex& other) const {
    float_alias real_result = ((real_part * other.real_part) - (imag_part * other.imag_part));
    float_alias imag_result = ((imag_part * other.real_part) + (real_part * other.imag_part));
    return Complex(real_result, imag_result);
}

Complex Complex::operator/(const Complex& other) const {
    float_alias denom = ((other.real_part * other.real_part) + (other.imag_part * other.imag_part));
    float_alias real_result = (((real_part * other.real_part) + (imag_part * other.imag_part)) / denom);
    float_alias imag_result = (((imag_part * other.real_part) - (real_part * other.imag_part)) / denom);
    return Complex(real_result, imag_result);
}

// Arithmetic with scalar (member functions)
Complex Complex::operator+(float_alias value) const {
    return Complex((real_part + value), imag_part);
}

Complex Complex::operator-(float_alias value) const {
    return Complex((real_part - value), imag_part);
}

Complex Complex::operator*(float_alias value) const {
    return Complex((real_part * value), (imag_part * value));
}

Complex Complex::operator/(float_alias value) const {
    return Complex((real_part / value), (imag_part / value));
}

// Arithmetic with scalar (non-member, friend functions)
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
    float_alias real_result = ((lhs * rhs.real_part) / denom);
    float_alias imag_result = ((-lhs * rhs.imag_part) / denom);
    return Complex(real_result, imag_result);
}

Complex Complex::conj() const {
    return Complex(real_part, (-imag_part));
}

float_alias Complex::abs() const {
    return std::sqrt(((real_part * real_part) + (imag_part * imag_part)));
}

Complex Complex::exp() const {
    float_alias exp_real = std::exp(real_part);
    float_alias real_result = (exp_real * std::cos(imag_part));
    float_alias imag_result = (exp_real * std::sin(imag_part));
    return Complex(real_result, imag_result);
}

}  // namespace complex_numbers
