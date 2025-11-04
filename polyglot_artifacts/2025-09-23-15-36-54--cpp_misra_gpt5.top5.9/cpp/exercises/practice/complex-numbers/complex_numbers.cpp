#include "complex_numbers.h"

#include <cmath>

#ifdef abs
#undef abs
#endif
#ifdef conj
#undef conj
#endif
#ifdef exp
#undef exp
#endif

namespace complex_numbers {

Complex::Complex() noexcept : real_(0.0), imag_(0.0) {}

Complex::Complex(double real_part, double imag_part) noexcept
    : real_(real_part), imag_(imag_part) {}

double Complex::real() const noexcept {
    return real_;
}

double Complex::imag() const noexcept {
    return imag_;
}

Complex Complex::conj() const noexcept {
    return Complex(real_, (0.0 - imag_));
}

double Complex::abs() const noexcept {
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::exp() const noexcept {
    const double factor = std::exp(real_);
    const double c = std::cos(imag());
    const double s = std::sin(imag());
    return Complex((factor * c), (factor * s));
}

// Free-function wrappers
Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

// Operators between complex numbers
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex((lhs.real() + rhs.real()), (lhs.imag() + rhs.imag()));
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex((lhs.real() - rhs.real()), (lhs.imag() - rhs.imag()));
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    const double a = lhs.real();
    const double b = lhs.imag();
    const double c = rhs.real();
    const double d = rhs.imag();
    return Complex(((a * c) - (b * d)), ((b * c) + (a * d)));
}

Complex operator/(const Complex& lhs, const Complex& rhs) noexcept {
    const double a = lhs.real();
    const double b = lhs.imag();
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    return Complex((((a * c) + (b * d)) / denom), (((b * c) - (a * d)) / denom));
}

// Mixed operators with real numbers (double on right)
Complex operator+(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

// Mixed operators with real numbers (double on left)
Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs - rhs.real()), (0.0 - rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    // (lhs + 0i) / (c + id) = ((lhs*c) + 0) / (c^2 + d^2) + ((0*c) - (lhs*d)) / (c^2 + d^2) i
    const double a = lhs;
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    return Complex(((a * c) / denom), (-(a * d) / denom));
}

}  // namespace complex_numbers
