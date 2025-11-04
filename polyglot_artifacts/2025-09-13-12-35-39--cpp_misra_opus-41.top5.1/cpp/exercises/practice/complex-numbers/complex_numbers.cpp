#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() 
    : real_part(0.0), imaginary_part(0.0) {
}

Complex::Complex(double real_value, double imaginary_value) 
    : real_part(real_value), imaginary_part(imaginary_value) {
}

double Complex::real() const {
    return real_part;
}

double Complex::imag() const {
    return imaginary_part;
}

Complex Complex::operator+(const Complex& other) const {
    double new_real = real_part + other.real_part;
    double new_imag = imaginary_part + other.imaginary_part;
    return Complex(new_real, new_imag);
}

Complex Complex::operator-(const Complex& other) const {
    double new_real = real_part - other.real_part;
    double new_imag = imaginary_part - other.imaginary_part;
    return Complex(new_real, new_imag);
}

Complex Complex::operator*(const Complex& other) const {
    double new_real = (real_part * other.real_part) - (imaginary_part * other.imaginary_part);
    double new_imag = (imaginary_part * other.real_part) + (real_part * other.imaginary_part);
    return Complex(new_real, new_imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = (other.real_part * other.real_part) + (other.imaginary_part * other.imaginary_part);
    double new_real = ((real_part * other.real_part) + (imaginary_part * other.imaginary_part)) / denominator;
    double new_imag = ((imaginary_part * other.real_part) - (real_part * other.imaginary_part)) / denominator;
    return Complex(new_real, new_imag);
}

Complex Complex::operator+(double value) const {
    double new_real = real_part + value;
    return Complex(new_real, imaginary_part);
}

Complex Complex::operator-(double value) const {
    double new_real = real_part - value;
    return Complex(new_real, imaginary_part);
}

Complex Complex::operator*(double value) const {
    double new_real = real_part * value;
    double new_imag = imaginary_part * value;
    return Complex(new_real, new_imag);
}

Complex Complex::operator/(double value) const {
    double new_real = real_part / value;
    double new_imag = imaginary_part / value;
    return Complex(new_real, new_imag);
}

Complex Complex::conj() const {
    return Complex(real_part, -imaginary_part);
}

double Complex::abs() const {
    return std::sqrt((real_part * real_part) + (imaginary_part * imaginary_part));
}

Complex Complex::exp() const {
    double exp_real = std::exp(real_part);
    double new_real = exp_real * std::cos(imaginary_part);
    double new_imag = exp_real * std::sin(imaginary_part);
    return Complex(new_real, new_imag);
}

// Non-member operators for double on left side
Complex operator+(double value, const Complex& c) {
    double new_real = value + c.real();
    return Complex(new_real, c.imag());
}

Complex operator-(double value, const Complex& c) {
    double new_real = value - c.real();
    double new_imag = -c.imag();
    return Complex(new_real, new_imag);
}

Complex operator*(double value, const Complex& c) {
    double new_real = value * c.real();
    double new_imag = value * c.imag();
    return Complex(new_real, new_imag);
}

Complex operator/(double value, const Complex& c) {
    // Division: value / (a + bi) = value * (a - bi) / (a^2 + b^2)
    double real_part = c.real();
    double imag_part = c.imag();
    double denominator = (real_part * real_part) + (imag_part * imag_part);
    double new_real = (value * real_part) / denominator;
    double new_imag = -(value * imag_part) / denominator;
    return Complex(new_real, new_imag);
}

}  // namespace complex_numbers
