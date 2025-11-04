#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex {
public:
    Complex() = default;
    Complex(float_alias real, float_alias imag);

    float_alias real() const;
    float_alias imag() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex conjugate() const;
    float_alias abs() const;
    Complex exp() const;

    // Add alternate name for conjugate
    Complex conj() const;

    // Arithmetic with real numbers
    Complex operator+(float_alias rhs) const;
    Complex operator-(float_alias rhs) const;
    Complex operator*(float_alias rhs) const;
    Complex operator/(float_alias rhs) const;

    // Friend functions for real op Complex
    friend Complex operator+(float_alias lhs, const Complex& rhs);
    friend Complex operator-(float_alias lhs, const Complex& rhs);
    friend Complex operator*(float_alias lhs, const Complex& rhs);
    friend Complex operator/(float_alias lhs, const Complex& rhs);

private:
    float_alias m_real;
    float_alias m_imag;
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
