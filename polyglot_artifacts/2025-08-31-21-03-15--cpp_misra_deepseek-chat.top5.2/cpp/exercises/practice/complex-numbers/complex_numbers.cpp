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
    return Complex(real_part, -imag_part);
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
    // (a + bi)*(c + di) = (ac - bd) + (ad + bc)i
    double real = ((real_part * other.real_part) - (imag_part * other.imag_part));
    double imag = ((real_part * other.imag_part) + (imag_part * other.real_part));
    return Complex(real, imag);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + bi)/(c + di) = [(ac + bd)/(c^2 + d^2)] + [(bc - ad)/(c^2 + d^2)]i
    double denominator = ((other.real_part * other.real_part) + (other.imag_part * other.imag_part));
    double real = (((real_part * other.real_part) + (imag_part * other.imag_part)) / denominator);
    double imag = (((imag_part * other.real_part) - (real_part * other.imag_part)) / denominator);
    return Complex(real, imag);
}

// Member operators for Complex op double
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

// Non-member operators for double op Complex
Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real()), ((-rhs.imag())));
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) {
    // To compute lhs / (a + bi), which is the same as lhs * conjugate / (a^2 + b^2)
    double denominator = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    double real = ((lhs * rhs.real()) / denominator);
    double imag = (((-lhs) * rhs.imag()) / denominator);
    return Complex(real, imag);
}

}  // namespace complex_numbers
