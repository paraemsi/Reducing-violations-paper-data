#include "complex_numbers.h"

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
    return Complex(real_part, -imag_part);
}

Complex Complex::exp() const {
    double exp_real = std::exp(real_part);
    return Complex((exp_real * std::cos(imag_part)), (exp_real * std::sin(imag_part)));
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_part + other.real_part, imag_part + other.imag_part);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_part - other.real_part, imag_part - other.imag_part);
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

// Implement operators for complex number and double
Complex Complex::operator+(double other) const {
    return Complex((real_part + other), imag_part);
}

Complex Complex::operator-(double other) const {
    return Complex((real_part - other), imag_part);
}

Complex Complex::operator*(double other) const {
    return Complex((real_part * other), (imag_part * other));
}

Complex Complex::operator/(double other) const {
    return Complex((real_part / other), (imag_part / other));
}

// Implement friend functions for double and complex number operations
namespace complex_numbers {

Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real_part), rhs.imag_part);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real_part), (-rhs.imag_part));
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real_part), (lhs * rhs.imag_part));
}

Complex operator/(double lhs, const Complex& rhs) {
    // To divide a double by a complex number, we can treat lhs as a complex number (lhs + 0i)
    // and use the complex division formula
    double denominator = ((rhs.real_part * rhs.real_part) + (rhs.imag_part * rhs.imag_part));
    double real = ((lhs * rhs.real_part) / denominator);
    double imag = (((-lhs) * rhs.imag_part) / denominator);
    return Complex(real, imag);
}

}  // namespace complex_numbers

}  // namespace complex_numbers
