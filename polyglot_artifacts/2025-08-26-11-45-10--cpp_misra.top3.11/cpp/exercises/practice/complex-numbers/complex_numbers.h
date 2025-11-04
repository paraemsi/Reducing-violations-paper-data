#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex
{
public:
    explicit Complex(float_alias real_value, float_alias imag_value);

    float_alias real(void) const;
    float_alias imag(void) const;

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    Complex conj(void) const;
    float_alias abs(void) const;
    Complex exp(void) const;

private:
    float_alias m_real;
    float_alias m_imag;
};

 // Scalar overloads for arithmetic with double on either side
Complex operator+(const Complex& lhs, float_alias rhs);
Complex operator+(float_alias lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, float_alias rhs);
Complex operator-(float_alias lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, float_alias rhs);
Complex operator*(float_alias lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, float_alias rhs);
Complex operator/(float_alias lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
