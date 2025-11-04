#include "complex_numbers.h"

#include <stdexcept>

namespace complex_numbers {

/* Compound division assignment */
Complex& Complex::operator/=(const Complex& rhs)
{
    const double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    if (denom == 0.0)
    {
        throw std::runtime_error("Division by zero complex number");
    }

    const double newReal = (((m_real * rhs.real()) + (m_imag * rhs.imag())) / denom);
    const double newImag = (((m_imag * rhs.real()) - (m_real * rhs.imag())) / denom);

    m_real = newReal;
    m_imag = newImag;

    return *this;
}

/* Scalar (double lhs) non-member operator definitions */
Complex operator+(double lhs, const Complex& rhs) noexcept
{
    Complex result(lhs, 0.0);
    result += rhs;
    return result;
}

/* Scalar (double rhs) non-member operator definitions */
Complex operator+(const Complex& lhs, double rhs) noexcept
{
    Complex result(lhs);
    result += Complex(rhs, 0.0);
    return result;
}

Complex operator-(const Complex& lhs, double rhs) noexcept
{
    Complex result(lhs);
    result -= Complex(rhs, 0.0);
    return result;
}

Complex operator*(const Complex& lhs, double rhs) noexcept
{
    Complex result(lhs);
    result *= Complex(rhs, 0.0);
    return result;
}

Complex operator/(const Complex& lhs, double rhs)
{
    if (rhs == 0.0)
    {
        throw std::runtime_error("Division by zero scalar");
    }
    Complex result(lhs);
    result /= Complex(rhs, 0.0);
    return result;
}

Complex operator-(double lhs, const Complex& rhs) noexcept
{
    Complex result(lhs, 0.0);
    result -= rhs;
    return result;
}

Complex operator*(double lhs, const Complex& rhs) noexcept
{
    Complex result(lhs, 0.0);
    result *= rhs;
    return result;
}

Complex operator/(double lhs, const Complex& rhs)
{
    Complex result(lhs, 0.0);
    result /= rhs;
    return result;
}

/* Exponential of a complex number */
Complex exp(const Complex& z)
{
    const double expReal = std::exp(z.real());
    const double cosImag = std::cos(z.imag());
    const double sinImag = std::sin(z.imag());

    const double realPart = expReal * cosImag;
    const double imagPart = expReal * sinImag;

    return Complex(realPart, imagPart);
}

Complex conj(const Complex& z) noexcept
{
    return z.conj();
}

double abs(const Complex& z) noexcept
{
    return z.abs();
}

}  // namespace complex_numbers
