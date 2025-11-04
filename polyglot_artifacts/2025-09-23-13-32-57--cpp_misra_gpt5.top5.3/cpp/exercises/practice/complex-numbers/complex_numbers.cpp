#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex() : m_real(0.0), m_imag(0.0) {}

Complex::Complex(double real, double imag)
    : m_real(real), m_imag(imag) {
}

double Complex::real() const {
    return m_real;
}

double Complex::imag() const {
    return m_imag;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex((m_real + other.m_real), (m_imag + other.m_imag));
}

Complex Complex::operator-(const Complex& other) const {
    return Complex((m_real - other.m_real), (m_imag - other.m_imag));
}

Complex Complex::operator*(const Complex& other) const {
    const double real_part = ((m_real * other.m_real) - (m_imag * other.m_imag));
    const double imag_part = ((m_imag * other.m_real) + (m_real * other.m_imag));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = ((other.m_real * other.m_real) + (other.m_imag * other.m_imag));
    const double real_part = (((m_real * other.m_real) + (m_imag * other.m_imag)) / denom);
    const double imag_part = (((m_imag * other.m_real) - (m_real * other.m_imag)) / denom);
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const {
    return Complex(m_real, (0.0 - m_imag));
}

double Complex::abs() const {
    return std::sqrt(((m_real * m_real) + (m_imag * m_imag)));
}

Complex Complex::exp() const {
    const double exp_real = std::exp(m_real);
    const double real_part = (exp_real * std::cos(m_imag));
    const double imag_part = (exp_real * std::sin(m_imag));
    return Complex(real_part, imag_part);
}

 // Support operations with a real number on the left-hand side
Complex operator+(double lhs, const Complex& rhs) {
    return (Complex(lhs, 0.0) + rhs);
}

Complex operator-(double lhs, const Complex& rhs) {
    return (Complex(lhs, 0.0) - rhs);
}

Complex operator*(double lhs, const Complex& rhs) {
    return (Complex(lhs, 0.0) * rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    return (Complex(lhs, 0.0) / rhs);
}

}  // namespace complex_numbers
