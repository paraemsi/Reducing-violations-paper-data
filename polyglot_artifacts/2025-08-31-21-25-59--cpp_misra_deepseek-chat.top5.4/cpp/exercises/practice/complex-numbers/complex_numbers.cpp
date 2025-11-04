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

Complex Complex::operator+(const Complex& other) const {
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const {
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const {
    double real_part = (real_ * other.real_) - (imag_ * other.imag_);
    double imag_part = (imag_ * other.real_) + (real_ * other.imag_);
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = (other.real_ * other.real_) + (other.imag_ * other.imag_);
    double real_part = ((real_ * other.real_) + (imag_ * other.imag_)) / denominator;
    double imag_part = ((imag_ * other.real_) - (real_ * other.imag_)) / denominator;
    return Complex(real_part, imag_part);
}

// Implement the new member operators
Complex Complex::operator+(double other) const {
    return Complex((real_ + other), imag_);
}

Complex Complex::operator-(double other) const {
    return Complex((real_ - other), imag_);
}

Complex Complex::operator*(double other) const {
    return Complex((real_ * other), (imag_ * other));
}

Complex Complex::operator/(double other) const {
    return Complex((real_ / other), (imag_ / other));
}

double Complex::abs() const {
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double magnitude = std::exp(real_);
    return Complex(magnitude * std::cos(imag_), magnitude * std::sin(imag_));
}

// Implement non-member operators
Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real()), -rhs.imag());
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) {
    // To divide a real number by a complex number, we can treat the real number as a complex number with imaginary part 0
    // and use the complex division formula
    Complex numerator(lhs, 0.0);
    return numerator / rhs;
}

}  // namespace complex_numbers
