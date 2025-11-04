#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_alias real_val, float_alias imag_val) noexcept
    : real_part(real_val), imag_part(imag_val) {}

float_alias Complex::real() const noexcept
{
    return real_part;
}

float_alias Complex::imag() const noexcept
{
    return imag_part;
}

Complex Complex::operator+(const Complex& rhs) const noexcept
{
    return Complex((real_part + rhs.real_part), (imag_part + rhs.imag_part));
}

Complex Complex::operator-(const Complex& rhs) const noexcept
{
    return Complex((real_part - rhs.real_part), (imag_part - rhs.imag_part));
}

Complex Complex::operator*(const Complex& rhs) const noexcept
{
    // (a + i*b) * (c + i*d) = (a*c - b*d) + (b*c + a*d)*i
    float_alias real_res = ((real_part * rhs.real_part) - (imag_part * rhs.imag_part));
    float_alias imag_res = ((imag_part * rhs.real_part) + (real_part * rhs.imag_part));
    return Complex(real_res, imag_res);
}

Complex Complex::operator+(float_alias rhs) const noexcept
{
    // (a + i*b) + r = (a + r) + i*b
    return Complex((real_part + rhs), imag_part);
}

Complex Complex::operator-(float_alias rhs) const noexcept
{
    // (a + i*b) - r = (a - r) + i*b
    return Complex((real_part - rhs), imag_part);
}

Complex Complex::operator*(float_alias rhs) const noexcept
{
    // (a + i*b) * r = (a*r) + i*(b*r)
    return Complex((real_part * rhs), (imag_part * rhs));
}

Complex Complex::operator/(float_alias rhs) const
{
    // (a + i*b) / r = (a/r) + i*(b/r)
    return Complex((real_part / rhs), (imag_part / rhs));
}

// Scalar on left
Complex operator+(Complex::float_alias lhs, const Complex& rhs) noexcept
{
    // r + (a + i*b) = (a + r) + i*b
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(Complex::float_alias lhs, const Complex& rhs) noexcept
{
    // r - (a + i*b) = (r - a) - i*b
    return Complex((lhs - rhs.real()), (-(rhs.imag())));
}

Complex operator*(Complex::float_alias lhs, const Complex& rhs) noexcept
{
    // r * (a + i*b) = (a*r) + i*(b*r)
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(Complex::float_alias lhs, const Complex& rhs)
{
    // r / (a + i*b) = r * (a - i*b) / (a^2 + b^2)
    Complex::float_alias denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    return Complex((lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom);
}

Complex Complex::operator/(const Complex& rhs) const
{
    // (a + i*b) / (c + i*d) = ((a*c + b*d)/(c^2 + d^2)) + ((b*c - a*d)/(c^2 + d^2))*i
    float_alias denom = ((rhs.real_part * rhs.real_part) + (rhs.imag_part * rhs.imag_part));
    if (denom == 0.0)
    {
        // Division by zero, behavior is undefined; here, return zero.
        return Complex(0.0, 0.0);
    }
    float_alias real_res = ((real_part * rhs.real_part) + (imag_part * rhs.imag_part)) / denom;
    float_alias imag_res = ((imag_part * rhs.real_part) - (real_part * rhs.imag_part)) / denom;
    return Complex(real_res, imag_res);
}

Complex Complex::conj() const noexcept
{
    return Complex(real_part, -imag_part);
}

Complex::float_alias Complex::abs() const noexcept
{
    // sqrt(a^2 + b^2)
    return std::sqrt((real_part * real_part) + (imag_part * imag_part));
}

Complex Complex::exp() const
{
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    float_alias exp_real = std::exp(real_part);
    float_alias real_res = exp_real * std::cos(imag_part);
    float_alias imag_res = exp_real * std::sin(imag_part);
    return Complex(real_res, imag_res);
}

}  // namespace complex_numbers
