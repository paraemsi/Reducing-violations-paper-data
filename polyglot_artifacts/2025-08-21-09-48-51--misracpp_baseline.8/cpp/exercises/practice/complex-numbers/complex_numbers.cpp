#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : re(real), im(imag) {}

Complex::Complex() : re(0.0), im(0.0) {}

double Complex::real() const {
    return re;
}

double Complex::imag() const {
    return im;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(re + other.re, im + other.im);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re - other.re, im - other.im);
}

Complex Complex::operator*(const Complex& other) const {
    // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
    double real_part = re * other.re - im * other.im;
    double imag_part = re * other.im + im * other.re;
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    // (a + bi) / (c + di) = [(ac + bd) + (bc - ad)i] / (c^2 + d^2)
    double denom = other.re * other.re + other.im * other.im;
    double real_part = (re * other.re + im * other.im) / denom;
    double imag_part = (im * other.re - re * other.im) / denom;
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const {
    return Complex(re, -im);
}

double Complex::abs() const {
    return std::sqrt(re * re + im * im);
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i sin(b))
    double exp_real = std::exp(re);
    return Complex(exp_real * std::cos(im), exp_real * std::sin(im));
}
// Arithmetic with double on right
Complex Complex::operator+(double rhs) const {
    return Complex(re + rhs, im);
}
Complex Complex::operator-(double rhs) const {
    return Complex(re - rhs, im);
}
Complex Complex::operator*(double rhs) const {
    return Complex(re * rhs, im * rhs);
}
Complex Complex::operator/(double rhs) const {
    return Complex(re / rhs, im / rhs);
}

// Friend functions for double on left
Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.re, rhs.im);
}
Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.re, -rhs.im);
}
Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.re, lhs * rhs.im);
}
Complex operator/(double lhs, const Complex& rhs) {
    // lhs / (a + bi) = (lhs * a)/(a^2 + b^2) - (lhs * b)/(a^2 + b^2) * i
    double denom = rhs.re * rhs.re + rhs.im * rhs.im;
    return Complex((lhs * rhs.re) / denom, (-lhs * rhs.im) / denom);
}

}  // namespace complex_numbers
