#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real) : real_(real), imag_(0.0) {}
Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a+ib)*(c+id) = (ac - bd) + i(bc + ad)
    const double a = real_;
    const double b = imag_;
    const double c = other.real_;
    const double d = other.imag_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const {
    // (a+ib)/(c+id) = ((ac+bd)/(c^2+d^2)) + i((bc - ad)/(c^2 + d^2))
    const double a = real_;
    const double b = imag_;
    const double c = other.real_;
    const double d = other.imag_;
    const double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    // e^(a+ib) = e^a (cos b + i sin b)
    const double e_to_a = std::exp(real_);
    return Complex(e_to_a * std::cos(imag_), e_to_a * std::sin(imag_));
}

 // Non-member operators to support real numbers on either side
Complex operator+(const Complex& lhs, double rhs) {
    return lhs + Complex(rhs);
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs) + rhs;
}

Complex operator-(const Complex& lhs, double rhs) {
    return lhs - Complex(rhs);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs) - rhs;
}

Complex operator*(const Complex& lhs, double rhs) {
    return lhs * Complex(rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs) * rhs;
}

Complex operator/(const Complex& lhs, double rhs) {
    return lhs / Complex(rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs) / rhs;
}

// Free function wrappers for convenience and API compatibility
double real(const Complex& z) { return z.real(); }
double imag(const Complex& z) { return z.imag(); }
Complex conj(const Complex& z) { return z.conj(); }
double abs(const Complex& z) { return z.abs(); }
Complex exp(const Complex& z) { return z.exp(); }

}  // namespace complex_numbers
