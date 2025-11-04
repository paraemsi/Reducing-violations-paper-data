#include "complex_numbers.h"
#include <stdexcept>

namespace complex_numbers {

Complex Complex::conjugate() const noexcept
{
    return Complex(real_, -imag_);
}

double Complex::abs() const noexcept
{
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

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
    const double result_real = ((real_ * other.real_) - (imag_ * other.imag_));
    const double result_imag = ((imag_ * other.real_) + (real_ * other.imag_));
    return Complex(result_real, result_imag);
}

Complex Complex::operator/(const Complex& other) const
{
    const double denominator = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
    if (denominator == 0.0)
    {
        throw std::invalid_argument("Division by zero complex number");
    }
    const double result_real = (((real_ * other.real_) + (imag_ * other.imag_)) / denominator);
    const double result_imag = (((imag_ * other.real_) - (real_ * other.imag_)) / denominator);
    return Complex(result_real, result_imag);
}

Complex conj(const Complex& z) noexcept
{
    return z.conjugate();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

Complex exp(const Complex& z)
{
    const double exp_real = std::exp(z.real());
    const double result_real = (exp_real * std::cos(z.imag()));
    const double result_imag = (exp_real * std::sin(z.imag()));
    return Complex(result_real, result_imag);
}

 // Scalar (double) on left-hand side overloads
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

Complex operator/(double lhs, const Complex& rhs)
{
    return Complex(lhs, 0.0) / rhs;
}

// Scalar (double) on right-hand side overloads
Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() + rhs), lhs.imag());
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() - rhs), lhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

Complex operator/(const Complex& lhs, double rhs)
{
    if (rhs == 0.0)
    {
        throw std::invalid_argument("Division by zero scalar");
    }
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

}  // namespace complex_numbers
