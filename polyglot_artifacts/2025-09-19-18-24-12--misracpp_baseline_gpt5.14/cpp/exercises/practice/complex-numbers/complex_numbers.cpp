#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double r, double i) : real_{r}, imag_{i} {}

double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

Complex Complex::operator+(const Complex& other) const {
    return Complex{real_ + other.real_, imag_ + other.imag_};
}

Complex Complex::operator-(const Complex& other) const {
    return Complex{real_ - other.real_, imag_ - other.imag_};
}

Complex Complex::operator*(const Complex& other) const {
    return Complex{real_ * other.real_ - imag_ * other.imag_,
                   imag_ * other.real_ + real_ * other.imag_};
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return Complex{(real_ * other.real_ + imag_ * other.imag_) / denom,
                   (imag_ * other.real_ - real_ * other.imag_) / denom};
}

Complex Complex::conj() const {
    return Complex{real_, -imag_};
}

double Complex::abs() const {
    return std::hypot(real_, imag_);
}

Complex Complex::exp() const {
    const double exp_r = std::exp(real_);
    return Complex{exp_r * std::cos(imag_), exp_r * std::sin(imag_)};
}

Complex Complex::operator+(double rhs) const {
    return Complex{real_ + rhs, imag_};
}

Complex Complex::operator-(double rhs) const {
    return Complex{real_ - rhs, imag_};
}

Complex Complex::operator*(double rhs) const {
    return Complex{real_ * rhs, imag_ * rhs};
}

Complex Complex::operator/(double rhs) const {
    return Complex{real_ / rhs, imag_ / rhs};
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex{lhs * rhs.real(), lhs * rhs.imag()};
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex{lhs + rhs.real(), rhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex{lhs - rhs.real(), -rhs.imag()};
}

Complex operator/(double lhs, const Complex& rhs) {
    const double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return Complex{lhs * rhs.real() / denom, -lhs * rhs.imag() / denom};
}


}  // namespace complex_numbers
