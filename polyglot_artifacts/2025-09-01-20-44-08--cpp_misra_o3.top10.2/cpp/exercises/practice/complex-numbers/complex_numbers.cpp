#include "complex_numbers.h"

namespace complex_numbers {

/*  Addition */
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real_ + rhs.real_), (lhs.imag_ + rhs.imag_));
}

/*  Subtraction */
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real_ - rhs.real_), (lhs.imag_ - rhs.imag_));
}

/*  Multiplication */
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    const double real_part = ((lhs.real_ * rhs.real_) - (lhs.imag_ * rhs.imag_));
    const double imag_part = ((lhs.imag_ * rhs.real_) + (lhs.real_ * rhs.imag_));
    return Complex(real_part, imag_part);
}

/*  Division */
Complex operator/(const Complex& lhs, const Complex& rhs)
{
    const double denom = ((rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_));
    /*  Behaviour is undefined for division by zero – caller’s responsibility  */
    const double real_part = (((lhs.real_ * rhs.real_) + (lhs.imag_ * rhs.imag_)) / denom);
    const double imag_part = (((lhs.imag_ * rhs.real_) - (lhs.real_ * rhs.imag_)) / denom);
    return Complex(real_part, imag_part);
}

/*  Conjugate */
Complex conjugate(const Complex& z) noexcept
{
    return Complex(z.real_, (-z.imag_));
}

/*  Absolute value (magnitude) */
double abs(const Complex& z) noexcept
{
    return std::sqrt(((z.real_ * z.real_) + (z.imag_ * z.imag_)));
}

/*  Exponential function using Euler’s formula */
Complex exp(const Complex& z) noexcept
{
    const double exp_real = std::exp(z.real_);
    const double real_part = (exp_real * std::cos(z.imag_));
    const double imag_part = (exp_real * std::sin(z.imag_));
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
