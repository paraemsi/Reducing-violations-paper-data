#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_{real}, imag_{imag} {}


double Complex::abs() const {
    return std::hypot(real_, imag_);
}

Complex Complex::exp() const {
    const auto exp_real = std::exp(real_);
    return Complex(exp_real * std::cos(imag_),
                   exp_real * std::sin(imag_));
}

Complex& Complex::operator+=(const Complex& other) {
    real_ += other.real();
    imag_ += other.imag();
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real_ -= other.real();
    imag_ -= other.imag();
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    const double temp_real = real_ * other.real() - imag_ * other.imag();
    imag_ = imag_ * other.real() + real_ * other.imag();
    real_ = temp_real;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    if (std::abs(other.real()) >= std::abs(other.imag())) {
        const double r = other.imag() / other.real();
        const double den = other.real() + r * other.imag();
        const double temp_real = (real_ + r * imag_) / den;
        imag_ = (imag_ - r * real_) / den;
        real_ = temp_real;
    } else {
        const double r = other.real() / other.imag();
        const double den = other.imag() + r * other.real();
        const double temp_real = (real_ * r + imag_) / den;
        imag_ = (imag_ * r - real_) / den;
        real_ = temp_real;
    }
    return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs) += rhs;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs) -= rhs;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs) *= rhs;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs) /= rhs;
}

}  // namespace complex_numbers
