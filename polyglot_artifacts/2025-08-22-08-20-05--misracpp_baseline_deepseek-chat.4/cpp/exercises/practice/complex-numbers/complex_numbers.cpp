#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

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
    double real_part = real_ * other.real_ - imag_ * other.imag_;
    double imag_part = imag_ * other.real_ + real_ * other.imag_;
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    double real_part = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double imag_part = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    return Complex(real_part, imag_part);
}

// Implement friend operators
namespace complex_numbers {

Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ + rhs, lhs.imag_);
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real_, rhs.imag_);
}

Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ - rhs, lhs.imag_);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real_, -rhs.imag_);
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ * rhs, lhs.imag_ * rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real_, lhs * rhs.imag_);
}

Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real_ / rhs, lhs.imag_ / rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    // To divide a double by a complex number, we can treat the double as a complex number with imaginary part 0
    // So it's (lhs + 0i) / (rhs.real_ + rhs.imag_i)
    double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
    double real_part = (lhs * rhs.real_) / denominator;
    double imag_part = (-lhs * rhs.imag_) / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers

}  // namespace complex_numbers
