#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double r, double i) : real_(r), imag_(i) {}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    double new_real = real_ * other.real_ - imag_ * other.imag_;
    double new_imag = imag_ * other.real_ + real_ * other.imag_;
    return Complex(new_real, new_imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denom;
    return Complex(new_real, new_imag);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    double e_real = std::exp(real_);
    double cos_imag = std::cos(imag_);
    double sin_imag = std::sin(imag_);
    return Complex(e_real * cos_imag, e_real * sin_imag);
}

// Non-member operators
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
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double new_real = (lhs * rhs.real()) / denom;
    double new_imag = (-lhs * rhs.imag()) / denom;
    return Complex(new_real, new_imag);
}

}  // namespace complex_numbers
