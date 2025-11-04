#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : r_(0.0), i_(0.0) {}
Complex::Complex(double real, double imag) noexcept : r_(real), i_(imag) {}

double Complex::real() const noexcept { return r_; }
double Complex::imag() const noexcept { return i_; }

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex(r_ + other.r_, i_ + other.i_);
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex(r_ - other.r_, i_ - other.i_);
}

Complex Complex::operator*(const Complex& other) const noexcept {
    // (a + ib) * (c + id) = (ac - bd) + (bc + ad)i
    double a = r_, b = i_;
    double c = other.r_, d = other.i_;
    return Complex(a * c - b * d, b * c + a * d);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    // (a + ib) / (c + id) = ((ac + bd) / (c^2 + d^2)) + ((bc - ad) / (c^2 + d^2)) i
    double a = r_, b = i_;
    double c = other.r_, d = other.i_;
    double denom = c * c + d * d;
    return Complex((a * c + b * d) / denom, (b * c - a * d) / denom);
}

Complex Complex::operator+(double rhs) const noexcept {
    return Complex(r_ + rhs, i_);
}

Complex Complex::operator-(double rhs) const noexcept {
    return Complex(r_ - rhs, i_);
}

Complex Complex::operator*(double rhs) const noexcept {
    return Complex(r_ * rhs, i_ * rhs);
}

Complex Complex::operator/(double rhs) const noexcept {
    return Complex(r_ / rhs, i_ / rhs);
}

Complex Complex::conj() const noexcept {
    return Complex(r_, -i_);
}

double Complex::abs() const noexcept {
    return std::sqrt(r_ * r_ + i_ * i_);
}

Complex Complex::exp() const {
    // e^(a + ib) = e^a * (cos b + i sin b)
    double ea = std::exp(r_);
    return Complex(ea * std::cos(i_), ea * std::sin(i_));
}

// Real on the left-hand side overloads
Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    // (x + 0i) / (c + id) = (x*c)/(c^2 + d^2) + (-x*d)/(c^2 + d^2) i
    double x = lhs;
    double c = rhs.real();
    double d = rhs.imag();
    double denom = c * c + d * d;
    return Complex((x * c) / denom, (-x * d) / denom);
}

Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) {
    return z.exp();
}

double real(const Complex& z) noexcept { return z.real(); }
double imag(const Complex& z) noexcept { return z.imag(); }

}  // namespace complex_numbers
