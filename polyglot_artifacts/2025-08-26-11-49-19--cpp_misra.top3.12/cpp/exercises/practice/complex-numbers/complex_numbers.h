#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex {
public:
    Complex(float_alias real_val, float_alias imag_val);

    float_alias real(void) const;
    float_alias imag(void) const;

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    Complex operator+(float_alias rhs) const;
    Complex operator-(float_alias rhs) const;
    Complex operator*(float_alias rhs) const;
    Complex operator/(float_alias rhs) const;

    friend Complex operator+(float_alias lhs, const Complex& rhs);
    friend Complex operator-(float_alias lhs, const Complex& rhs);
    friend Complex operator*(float_alias lhs, const Complex& rhs);
    friend Complex operator/(float_alias lhs, const Complex& rhs);

    Complex conj(void) const;
    Complex exp(void) const;
    float_alias abs(void) const;

private:
    float_alias real_part;
    float_alias imag_part;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
