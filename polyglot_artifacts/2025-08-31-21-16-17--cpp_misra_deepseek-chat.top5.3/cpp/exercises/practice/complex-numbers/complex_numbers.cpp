#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_part(real), imag_part(imag) {}

double Complex::real() const {
    return real_part;
}

double Complex::imag() const {
    return imag_part;
}

double Complex::abs() const {
    return std::sqrt(((real_part * real_part) + (imag_part * imag_part)));
}

Complex Complex::conj() const {
    return Complex(real_part, (-imag_part));
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double magnitude = std::exp(real_part);
    return Complex((magnitude * std::cos(imag_part)), (magnitude * std::sin(imag_part)));
}

Complex Complex::operator+(const Complex& other) const {
    return Complex((real_part + other.real_part), (imag_part + other.imag_part));
}

Complex Complex::operator-(const Complex& other) const {
    return Complex((real_part - other.real_part), (imag_part - other.imag_part));
}

Complex Complex::operator*(const Complex& other) const {
    double real = ((real_part * other.real_part) - (imag_part * other.imag_part));
    double imag = ((imag_part * other.real_part) + (real_part * other.imag_part));
    return Complex(real, imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = ((other.real_part * other.real_part) + (other.imag_part * other.imag_part));
    double real = (((real_part * other.real_part) + (imag_part * other.imag_part)) / denominator);
    double imag = (((imag_part * other.real_part) - (real_part * other.imag_part)) / denominator);
    return Complex(real, imag);
}

// Implement friend functions for operations with doubles
Complex operator+(const Complex& c, double d) {
    return Complex((c.real_part + d), c.imag_part);
}

Complex operator+(double d, const Complex& c) {
    return Complex((d + c.real_part), c.imag_part);
}

Complex operator-(const Complex& c, double d) {
    return Complex((c.real_part - d), c.imag_part);
}

Complex operator-(double d, const Complex& c) {
    return Complex((d - c.real_part), (-c.imag_part));
}

Complex operator*(const Complex& c, double d) {
    return Complex((c.real_part * d), (c.imag_part * d));
}

Complex operator*(double d, const Complex& c) {
    return Complex((d * c.real_part), (d * c.imag_part));
}

Complex operator/(const Complex& c, double d) {
    return Complex((c.real_part / d), (c.imag_part / d));
}

Complex operator/(double d, const Complex& c) {
    // To compute d / (a + bi), we can treat d as (d + 0i)
    // and use the division formula for complex numbers
    double denominator = ((c.real_part * c.real_part) + (c.imag_part * c.imag_part));
    double real = ((d * c.real_part) / denominator);
    double imag = ((0.0 - (d * c.imag_part)) / denominator);
    return Complex(real, imag);
}

}  // namespace complex_numbers
