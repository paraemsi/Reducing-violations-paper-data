#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}
Complex::Complex(double real) : real_(real), imag_(0.0) {}

double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double magnitude = std::exp(real_);
    return Complex(magnitude * std::cos(imag_), magnitude * std::sin(imag_));
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + bi)*(c + di) = (ac - bd) + (ad + bc)i
    double real_part = real_ * other.real_ - imag_ * other.imag_;
    double imag_part = real_ * other.imag_ + imag_ * other.real_;
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + bi)/(c + di) = [(ac + bd)/(c^2 + d^2)] + [(bc - ad)/(c^2 + d^2)]i
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    double real_part = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double imag_part = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    return Complex(real_part, imag_part);
}

// Implement non-member operators
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
    // To compute lhs / (a + bi), which is the same as lhs * (1/(a + bi))
    // 1/(a + bi) = a/(a^2 + b^2) - b/(a^2 + b^2)i
    double denominator = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double real_part = rhs.real() / denominator;
    double imag_part = -rhs.imag() / denominator;
    return Complex(lhs * real_part, lhs * imag_part);
}

}  // namespace complex_numbers
