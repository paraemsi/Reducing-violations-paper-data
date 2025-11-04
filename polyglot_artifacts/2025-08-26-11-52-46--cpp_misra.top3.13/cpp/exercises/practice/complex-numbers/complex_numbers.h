#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_type = double;

class Complex {
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

    Complex conj(void) const;
    float_type abs(void) const;
    Complex exp(void) const;

    friend Complex operator+(float_type lhs, const Complex& rhs);
    friend Complex operator-(float_type lhs, const Complex& rhs);
    friend Complex operator*(float_type lhs, const Complex& rhs);
    friend Complex operator/(float_type lhs, const Complex& rhs);

private:
    float_type m_real;
    float_type m_imag;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
