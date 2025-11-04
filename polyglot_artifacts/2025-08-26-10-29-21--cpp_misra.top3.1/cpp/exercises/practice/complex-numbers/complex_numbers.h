#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex
{
public:
    Complex(float_alias real_value, float_alias imag_value);

    float_alias real(void) const;
    float_alias imag(void) const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Overloads for Complex op double
    Complex operator+(float_alias value) const;
    Complex operator-(float_alias value) const;
    Complex operator*(float_alias value) const;
    Complex operator/(float_alias value) const;

    // Friends for double op Complex
    friend Complex operator+(float_alias lhs, const Complex& rhs);
    friend Complex operator-(float_alias lhs, const Complex& rhs);
    friend Complex operator*(float_alias lhs, const Complex& rhs);
    friend Complex operator/(float_alias lhs, const Complex& rhs);

    Complex conj(void) const;
    float_alias abs(void) const;
    Complex exp(void) const;

    // Expose real and imag for friend functions
    float_alias get_real(void) const { return m_real; }
    float_alias get_imag(void) const { return m_imag; }

private:
    float_alias m_real;
    float_alias m_imag;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
