#include "complex_numbers.h"
#include <stdexcept>

namespace complex_numbers {

Complex Complex::operator+(const Complex& other) const noexcept
{
    return Complex((real_ + other.real_), (imag_ + other.imag_));
}

Complex Complex::operator-(const Complex& other) const noexcept
{
    return Complex((real_ - other.real_), (imag_ - other.imag_));
}

Complex Complex::operator*(const Complex& other) const noexcept
{
    double const new_real = ((real_ * other.real_) - (imag_ * other.imag_));
    double const new_imag = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(new_real, new_imag);
}

Complex Complex::operator/(const Complex& other) const
{
    double const denominator = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    if (denominator == 0.0)
    {
        throw std::invalid_argument("Division by zero complex number");
    }
    double const new_real = (((real_ * other.real_) + (imag_ * other.imag_)) / denominator);
    double const new_imag = (((imag_ * other.real_) - (real_ * other.imag_)) / denominator);
    return Complex(new_real, new_imag);
}

Complex Complex::conjugate() const noexcept
{
    return Complex(real_, (-imag_));
}

double Complex::abs() const noexcept
{
    return std::sqrt(((real_ * real_) + (imag_ * imag_)));
}

Complex Complex::exp() const
{
    double const e_to_real = std::exp(real_);
    double const cos_imag = std::cos(imag_);
    double const sin_imag = std::sin(imag_);
    return Complex((e_to_real * cos_imag), (e_to_real * sin_imag));
}

Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) + rhs;
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) - rhs;
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) * rhs;
}

Complex operator/(double lhs, const Complex& rhs)
{
    return Complex(lhs, 0.0) / rhs;
}

Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return lhs + Complex(rhs, 0.0);
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return lhs - Complex(rhs, 0.0);
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return lhs * Complex(rhs, 0.0);
}

Complex operator/(const Complex& lhs, double rhs)
{
    return lhs / Complex(rhs, 0.0);
}

}  // namespace complex_numbers
