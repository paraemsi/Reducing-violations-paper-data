#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

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

double Complex::abs() const {
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::conj() const {
    return Complex(real_, (-imag_));
}

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
    // To compute lhs / (a + bi), we can use the formula for division
    // Multiply numerator and denominator by the conjugate
    double denominator = (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag());
    double real_part = (lhs * rhs.real()) / denominator;
    double imag_part = ((-lhs) * rhs.imag()) / denominator;
    return Complex(real_part, imag_part);
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double magnitude = std::exp(real_);
    return Complex((magnitude * std::cos(imag_)), (magnitude * std::sin(imag_)));
}

}  // namespace complex_numbers
