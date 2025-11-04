#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_type = double;

class Complex
{
public:
    explicit Complex(float_type real_value, float_type imag_value);

    float_type real(void) const;
    float_type imag(void) const;

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    // Overloads for arithmetic with double on right
    Complex operator+(float_type rhs) const;
    Complex operator-(float_type rhs) const;
    Complex operator*(float_type rhs) const;
    Complex operator/(float_type rhs) const;

    // Friend overloads for arithmetic with double on left
    friend Complex operator+(float_type lhs, const Complex& rhs);
    friend Complex operator-(float_type lhs, const Complex& rhs);
    friend Complex operator*(float_type lhs, const Complex& rhs);
    friend Complex operator/(float_type lhs, const Complex& rhs);

    Complex conj(void) const;
    float_type abs(void) const;
    Complex exp(void) const;

private:
    float_type m_real;
    float_type m_imag;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
