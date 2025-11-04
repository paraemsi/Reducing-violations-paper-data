#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex
{
public:
    Complex(float_alias real_val, float_alias imag_val) noexcept;

    float_alias real() const noexcept;
    float_alias imag() const noexcept;

    Complex operator+(const Complex& rhs) const noexcept;
    Complex operator-(const Complex& rhs) const noexcept;
    Complex operator*(const Complex& rhs) const noexcept;
    Complex operator/(const Complex& rhs) const;

    // Scalar overloads
    Complex operator+(float_alias rhs) const noexcept;
    Complex operator-(float_alias rhs) const noexcept;
    Complex operator*(float_alias rhs) const noexcept;
    Complex operator/(float_alias rhs) const;

    Complex conj() const noexcept;
    float_alias abs() const noexcept;
    Complex exp() const;

    // Friend functions for scalar on left
    friend Complex operator+(float_alias lhs, const Complex& rhs) noexcept;
    friend Complex operator-(float_alias lhs, const Complex& rhs) noexcept;
    friend Complex operator*(float_alias lhs, const Complex& rhs) noexcept;
    friend Complex operator/(float_alias lhs, const Complex& rhs);

private:
    float_alias real_part;
    float_alias imag_part;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
