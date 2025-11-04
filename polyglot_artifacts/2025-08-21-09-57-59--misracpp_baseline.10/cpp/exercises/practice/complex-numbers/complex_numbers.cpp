#include "complex_numbers.h"

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
    return Complex(
        re * other.re - im * other.im,
        im * other.re + re * other.im
    );
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.re * other.re + other.im * other.im;
    return Complex(
        (re * other.re + im * other.im) / denom,
        (im * other.re - re * other.im) / denom
    );
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
    return Complex(
        exp_re * std::cos(im),
        exp_re * std::sin(im)
    );
}

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
    return Complex(
        (lhs * rhs.re) / denom,
        (-lhs * rhs.im) / denom
    );
}

}  // namespace complex_numbers
