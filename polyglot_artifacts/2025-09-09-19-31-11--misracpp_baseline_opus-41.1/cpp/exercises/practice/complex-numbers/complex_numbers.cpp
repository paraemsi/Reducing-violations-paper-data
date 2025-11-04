#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real_part, double imag_part) : real_(real_part), imag_(imag_part) {}

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
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    double exp_real = std::exp(real_);
    return Complex(exp_real * std::cos(imag_), exp_real * std::sin(imag_));
}

Complex Complex::operator+(const Complex& other) const {
    // (a + i*b) + (c + i*d) = (a + c) + (b + d)*i
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    // (a + i*b) - (c + i*d) = (a - c) + (b - d)*i
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + i*b) * (c + i*d) = (a*c - b*d) + (b*c + a*d)*i
    double new_real = real_ * other.real_ - imag_ * other.imag_;
    double new_imag = imag_ * other.real_ + real_ * other.imag_;
    return Complex(new_real, new_imag);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + i*b) / (c + i*d) = (a*c + b*d)/(c^2 + d^2) + (b*c - a*d)/(c^2 + d^2)*i
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    return Complex(new_real, new_imag);
}

// Non-member operator functions for double on the left side
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real_, rhs.imag_);
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real_, -rhs.imag_);
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real_, lhs * rhs.imag_);
}

Complex operator/(double lhs, const Complex& rhs) {
    // lhs / (a + i*b) = lhs * (1 / (a + i*b))
    // 1 / (a + i*b) = a/(a^2 + b^2) - b/(a^2 + b^2) * i
    double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
    double new_real = lhs * rhs.real_ / denominator;
    double new_imag = -lhs * rhs.imag_ / denominator;
    return Complex(new_real, new_imag);
}

}  // namespace complex_numbers
