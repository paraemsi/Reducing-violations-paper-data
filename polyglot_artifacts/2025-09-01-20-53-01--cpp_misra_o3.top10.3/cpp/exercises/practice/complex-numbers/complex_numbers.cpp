#include "complex_numbers.h"

#include <cmath>
#include <stdexcept>

namespace complex_numbers {

constexpr Complex::Complex(double real_val, double imag_val) noexcept
    : real_{real_val}, imag_{imag_val}
{
}

constexpr double Complex::real() const noexcept
{
    return real_;
}

constexpr double Complex::imag() const noexcept
{
    return imag_;
}

Complex Complex::conj() const noexcept
{
    return Complex{real_, -imag_};
}

Complex Complex::conjugate() const noexcept
{
    return conj();
}

double Complex::abs() const noexcept
{
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::exp() const noexcept
{
    double const exp_real{std::exp(real_)};
    return Complex{exp_real * std::cos(imag_), exp_real * std::sin(imag_)};
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{lhs.real_ + rhs.real_, lhs.imag_ + rhs.imag_};
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex{lhs.real_ - rhs.real_, lhs.imag_ - rhs.imag_};
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    double const real_part{(lhs.real_ * rhs.real_) - (lhs.imag_ * rhs.imag_)};
    double const imag_part{(lhs.imag_ * rhs.real_) + (lhs.real_ * rhs.imag_)};
    return Complex{real_part, imag_part};
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    double const denominator{(rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_)};

    if(denominator == 0.0)
    {
        throw std::invalid_argument("Division by zero complex");
    }

    double const real_part{((lhs.real_ * rhs.real_) + (lhs.imag_ * rhs.imag_)) / denominator};
    double const imag_part{((lhs.imag_ * rhs.real_) - (lhs.real_ * rhs.imag_)) / denominator};

    return Complex{real_part, imag_part};
}

Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex{lhs.real_ + rhs, lhs.imag_};
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex{lhs + rhs.real_, rhs.imag_};
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex{lhs.real_ - rhs, lhs.imag_};
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex{lhs - rhs.real_, -rhs.imag_};
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex{lhs.real_ * rhs, lhs.imag_ * rhs};
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex{lhs * rhs.real_, lhs * rhs.imag_};
}

Complex operator/(const Complex& lhs, double rhs)
{
    if(rhs == 0.0)
    {
        throw std::invalid_argument("Division by zero real scalar");
    }
    return Complex{lhs.real_ / rhs, lhs.imag_ / rhs};
}

Complex operator/(double lhs, const Complex& rhs)
{
    return Complex{lhs, 0.0} / rhs;
}

}  // namespace complex_numbers
