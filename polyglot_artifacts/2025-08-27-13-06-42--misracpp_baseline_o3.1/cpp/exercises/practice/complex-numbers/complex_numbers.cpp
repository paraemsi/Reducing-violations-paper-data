#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : r_(real), i_(imag) {}

double Complex::real() const {
    return r_;
}

double Complex::imag() const {
    return i_;
}

Complex Complex::operator+(const Complex &other) const {
    return {r_ + other.r_, i_ + other.i_};
}

Complex Complex::operator-(const Complex &other) const {
    return {r_ - other.r_, i_ - other.i_};
}

Complex Complex::operator*(const Complex &other) const {
    return {r_ * other.r_ - i_ * other.i_, i_ * other.r_ + r_ * other.i_};
}

Complex Complex::operator/(const Complex &other) const {
    double denom = other.r_ * other.r_ + other.i_ * other.i_;
    return {(r_ * other.r_ + i_ * other.i_) / denom,
            (i_ * other.r_ - r_ * other.i_) / denom};
}

Complex Complex::conj() const {
    return {r_, -i_};
}

double Complex::abs() const {
    return std::sqrt(r_ * r_ + i_ * i_);
}

Complex Complex::exp() const {
    double exp_real = std::exp(r_);
    return {exp_real * std::cos(i_), exp_real * std::sin(i_)};
}

Complex Complex::operator+(double other) const {
    return {r_ + other, i_};
}

Complex Complex::operator-(double other) const {
    return {r_ - other, i_};
}

Complex Complex::operator*(double other) const {
    return {r_ * other, i_ * other};
}

Complex Complex::operator/(double other) const {
    return {r_ / other, i_ / other};
}

// free functions for scalar on left-hand side
Complex operator+(double lhs, const Complex &rhs) {
    return rhs + lhs;
}

Complex operator-(double lhs, const Complex &rhs) {
    return {lhs - rhs.real(), -rhs.imag()};
}

Complex operator*(double lhs, const Complex &rhs) {
    return rhs * lhs;
}

Complex operator/(double lhs, const Complex &rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return {lhs * rhs.real() / denom, -lhs * rhs.imag() / denom};
}

}  // namespace complex_numbers
