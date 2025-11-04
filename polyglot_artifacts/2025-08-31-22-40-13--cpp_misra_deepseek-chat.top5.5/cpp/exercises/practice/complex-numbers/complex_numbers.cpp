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
    return std::sqrt((real_part * real_part) + (imag_part * imag_part));
}

Complex Complex::conj() const {
    return Complex(real_part, -imag_part);
}

Complex Complex::exp() const {
    double exp_real = std::exp(real_part);
    return Complex(exp_real * std::cos(imag_part), exp_real * std::sin(imag_part));
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_part + other.real_part, imag_part + other.imag_part);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_part - other.real_part, imag_part - other.imag_part);
}

Complex Complex::operator*(const Complex& other) const {
    double real = (real_part * other.real_part) - (imag_part * other.imag_part);
    double imag = (imag_part * other.real_part) + (real_part * other.imag_part);
    return Complex(real, imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = (other.real_part * other.real_part) + (other.imag_part * other.imag_part);
    double real = ((real_part * other.real_part) + (imag_part * other.imag_part)) / denominator;
    double imag = ((imag_part * other.real_part) - (real_part * other.imag_part)) / denominator;
    return Complex(real, imag);
}

// Implement operators with doubles
Complex Complex::operator+(double other) const {
    return Complex(real_part + other, imag_part);
}

Complex Complex::operator-(double other) const {
    return Complex(real_part - other, imag_part);
}

Complex Complex::operator*(double other) const {
    return Complex(real_part * other, imag_part * other);
}

Complex Complex::operator/(double other) const {
    return Complex(real_part / other, imag_part / other);
}

// Implement non-member operators for commutative operations
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(double lhs, const Complex& rhs) {
    // To divide a real number by a complex number, we can treat lhs as a complex number with imaginary part 0
    // and use the existing division implementation
    Complex temp(lhs, 0.0);
    return temp / rhs;
}

}  // namespace complex_numbers
