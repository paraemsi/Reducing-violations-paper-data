#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {


Complex Complex::conj() const noexcept {
    return Complex(m_real, -m_imag);
}

double Complex::abs() const noexcept {
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::exp() const noexcept {
    const double magnitude { std::exp(m_real) };
    return Complex((magnitude * std::cos(m_imag)),
                   (magnitude * std::sin(m_imag)));
}

// Operator implementations (non-member, symmetrical)
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex((lhs.real() + rhs.real()),
                   (lhs.imag() + rhs.imag()));
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex((lhs.real() - rhs.real()),
                   (lhs.imag() - rhs.imag()));
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    const double real_part { (lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag()) };
    const double imag_part { (lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag()) };
    return Complex(real_part, imag_part);
}

Complex operator+(const Complex& lhs, double rhs) noexcept {
    return operator+(lhs, Complex(rhs, 0.0));
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return operator+(Complex(lhs, 0.0), rhs);
}

Complex operator-(const Complex& lhs, double rhs) noexcept {
    return operator-(lhs, Complex(rhs, 0.0));
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return operator-(Complex(lhs, 0.0), rhs);
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return operator*(rhs, lhs);
}

Complex operator/(const Complex& lhs, double rhs) {
    if ((rhs == 0.0)) {
        throw std::domain_error("Division by zero in complex_numbers::operator/(Complex,double)");
    }
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

Complex operator/(double lhs, const Complex& rhs) {
    return operator/(Complex(lhs, 0.0), rhs);
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    const double denominator { (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()) };
    if (denominator == 0.0) {
        throw std::domain_error("Division by zero in complex_numbers::operator/");
    }

    const double real_part { ((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / denominator };
    const double imag_part { ((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / denominator };

    return Complex(real_part, imag_part);
}

// Free function wrappers
Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

}  // namespace complex_numbers
