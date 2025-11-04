#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : re(real), im(imag) {}

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
    double denominator = other.re * other.re + other.im * other.im;
    double real_part = (re * other.re + im * other.im) / denominator;
    double imag_part = (im * other.re - re * other.im) / denominator;
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
    double exp_re = std::exp(re);
    return Complex(exp_re * std::cos(im), exp_re * std::sin(im));
}

Complex operator+(double lhs, const Complex& rhs) {
    // (a) + (c + di) = (a + c) + di
    return Complex(lhs + rhs.re, rhs.im);
}

Complex operator-(double lhs, const Complex& rhs) {
    // (a) - (c + di) = (a - c) - di
    return Complex(lhs - rhs.re, -rhs.im);
}

Complex operator*(double lhs, const Complex& rhs) {
    // (a) * (c + di) = (a * c) + (a * d)i
    return Complex(lhs * rhs.re, lhs * rhs.im);
}

Complex operator/(double lhs, const Complex& rhs) {
    // (a) / (c + di) = [a * c / (c^2 + d^2)] + [-a * d / (c^2 + d^2)]i
    double denominator = rhs.re * rhs.re + rhs.im * rhs.im;
    double real_part = lhs * rhs.re / denominator;
    double imag_part = -lhs * rhs.im / denominator;
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
