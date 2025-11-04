#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_type = double;

class Complex
{
public:
    Complex(float_type real, float_type imag);

    float_type real(void) const;
    float_type imag(void) const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex operator+(float_type value) const;
    Complex operator-(float_type value) const;
    Complex operator*(float_type value) const;
    Complex operator/(float_type value) const;

    // Friend functions must be declared outside the class in the same namespace
    // so we will remove these from here and declare them after the class.

    Complex conj(void) const;
    float_type abs(void) const;
    Complex exp(void) const;

private:
    float_type m_real;
    float_type m_imag;
};

}  // namespace complex_numbers

// Friend functions for arithmetic with float_type (float_type op Complex)
complex_numbers::Complex operator+(complex_numbers::float_type lhs, const complex_numbers::Complex& rhs);
complex_numbers::Complex operator-(complex_numbers::float_type lhs, const complex_numbers::Complex& rhs);
complex_numbers::Complex operator*(complex_numbers::float_type lhs, const complex_numbers::Complex& rhs);
complex_numbers::Complex operator/(complex_numbers::float_type lhs, const complex_numbers::Complex& rhs);

#endif  // COMPLEX_NUMBERS_H

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
