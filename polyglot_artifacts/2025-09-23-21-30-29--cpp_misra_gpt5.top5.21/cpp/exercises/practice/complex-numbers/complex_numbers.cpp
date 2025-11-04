#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

double Complex::real() const noexcept
{
    return re;
}

double Complex::imag() const noexcept
{
    return im;
}

Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex((re + other.re), (im + other.im));
}

Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex((re - other.re), (im - other.im));
}

Complex Complex::operator*(const Complex& other) const noexcept
{
    const double real_part = ((re * other.re) - (im * other.im));
    const double imag_part = ((im * other.re) + (re * other.im));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const noexcept
{
    const double denom = ((other.re * other.re) + (other.im * other.im));
    const double real_num = ((re * other.re) + (im * other.im));
    const double imag_num = ((im * other.re) - (re * other.im));
    return Complex((real_num / denom), (imag_num / denom));
}

Complex Complex::operator+(double rhs) const noexcept
{
    return Complex((re + rhs), im);
}

Complex Complex::operator-(double rhs) const noexcept
{
    return Complex((re - rhs), im);
}

Complex Complex::operator*(double rhs) const noexcept
{
    return Complex((re * rhs), (im * rhs));
}

Complex Complex::operator/(double rhs) const noexcept
{
    return Complex((re / rhs), (im / rhs));
}

Complex Complex::conj() const noexcept
{
    return Complex(re, (-im));
}

double Complex::abs() const noexcept
{
    return std::sqrt(((re * re) + (im * im)));
}

Complex Complex::exp() const noexcept
{
    const double exp_real = std::exp(re);
    const double real_part = (exp_real * std::cos(im));
    const double imag_part = (exp_real * std::sin(im));
    return Complex(real_part, imag_part);
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) noexcept
{
    // (lhs + 0i) / (c + id) = (lhs*c)/(c^2 + d^2) + (0*c - lhs*d)/(c^2 + d^2)i
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    const double real_part = ((lhs * c) / denom);
    const double imag_part = ((-lhs * d) / denom);
    return Complex(real_part, imag_part);
}

// free-function helpers
double real(const Complex& z) noexcept
{
    return z.real();
}

double imag(const Complex& z) noexcept
{
    return z.imag();
}

Complex conj(const Complex& z) noexcept
{
    return z.conj();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

Complex exp(const Complex& z) noexcept
{
    return z.exp();
}

}  // namespace complex_numbers
