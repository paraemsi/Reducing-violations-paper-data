#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() : re_(0.0), im_(0.0) {}
Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const { return re_; }
double Complex::imag() const { return im_; }

Complex Complex::operator+(const Complex& other) const {
    return Complex{re_ + other.re_, im_ + other.im_};
}

Complex Complex::operator-(const Complex& other) const {
    return Complex{re_ - other.re_, im_ - other.im_};
}

Complex Complex::operator*(const Complex& other) const {
    // (a + i b) * (c + i d) = (ac - bd) + (bc + ad) i
    double a = re_, b = im_;
    double c = other.re_, d = other.im_;
    return Complex{a * c - b * d, b * c + a * d};
}

Complex Complex::operator/(const Complex& other) const {
    // (a + i b) / (c + i d) = (ac + bd)/(c^2 + d^2) + (bc - ad)/(c^2 + d^2) i
    double a = re_, b = im_;
    double c = other.re_, d = other.im_;
    double den = c * c + d * d;
    return Complex{(a * c + b * d) / den, (b * c - a * d) / den};
}

Complex Complex::operator+() const {
    return *this;
}

Complex Complex::operator-() const {
    return Complex{-re_, -im_};
}

bool Complex::operator==(const Complex& other) const {
    return re_ == other.re_ && im_ == other.im_;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// Operations with real numbers
Complex Complex::operator+(double other) const {
    return Complex{re_ + other, im_};
}

Complex Complex::operator-(double other) const {
    return Complex{re_ - other, im_};
}

Complex Complex::operator*(double other) const {
    return Complex{re_ * other, im_ * other};
}

Complex Complex::operator/(double other) const {
    return Complex{re_ / other, im_ / other};
}

// Non-member overloads with real on the left-hand side
Complex operator+(double lhs, const Complex& rhs) {
    return Complex{lhs + rhs.real(), rhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex{lhs - rhs.real(), -rhs.imag()};
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex{lhs * rhs.real(), lhs * rhs.imag()};
}

Complex operator/(double lhs, const Complex& rhs) {
    double c = rhs.real();
    double d = rhs.imag();
    double den = c * c + d * d;
    return Complex{(lhs * c) / den, (-lhs * d) / den};
}

Complex Complex::conjugate() const {
    return Complex{re_, -im_};
}

Complex Complex::conj() const {
    return Complex{re_, -im_};
}

double Complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    // e^(a + i b) = e^a * (cos b + i sin b)
    double ea = std::exp(re_);
    return Complex{ea * std::cos(im_), ea * std::sin(im_)};
}

// Free function wrappers for convenience
double real(const Complex& z) { return z.real(); }
double imag(const Complex& z) { return z.imag(); }
double abs(const Complex& z) { return z.abs(); }
Complex conj(const Complex& z) { return z.conj(); }
Complex exp(const Complex& z) { return z.exp(); }

}  // namespace complex_numbers
