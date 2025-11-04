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

    // Scalar overloads
    Complex operator+(float_alias rhs) const;
    Complex operator-(float_alias rhs) const;
    Complex operator*(float_alias rhs) const;
    Complex operator/(float_alias rhs) const;

private:
    float_alias real_part;
    float_alias imag_part;

public:
    Complex conj(void) const;
    float_alias abs(void) const;
    Complex exp(void) const;

    // Rule of five: add defaulted destructor, copy/move constructor and assignment
    ~Complex(void) = default;
    Complex(const Complex&) = default;
    Complex(Complex&&) = default;
    Complex& operator=(const Complex&) = default;
    Complex& operator=(Complex&&) = default;

    friend Complex operator+(float_alias lhs, const Complex& rhs);
    friend Complex operator-(float_alias lhs, const Complex& rhs);
    friend Complex operator*(float_alias lhs, const Complex& rhs);
    friend Complex operator/(float_alias lhs, const Complex& rhs);
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
