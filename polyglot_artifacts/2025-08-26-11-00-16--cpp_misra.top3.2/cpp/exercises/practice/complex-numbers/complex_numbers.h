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

    // Overloads for arithmetic with real numbers
    Complex operator+(float_alias rhs) const;
    Complex operator-(float_alias rhs) const;
    Complex operator*(float_alias rhs) const;
    Complex operator/(float_alias rhs) const;

    Complex conjugate(void) const;
    float_alias abs(void) const;
    Complex exp(void) const;

    // conj() alias for conjugate()
    Complex conj(void) const;

    // Rule of five: add defaulted destructor, copy/move constructors and assignment operators
    ~Complex() = default;
    Complex(const Complex&) = default;
    Complex(Complex&&) = default;
    Complex& operator=(const Complex&) = default;
    Complex& operator=(Complex&&) = default;

private:
    float_alias real_part;
    float_alias imag_part;
};

}  // namespace complex_numbers

// Non-member operator overloads for real op Complex
inline complex_numbers::Complex operator+(complex_numbers::float_alias lhs, const complex_numbers::Complex& rhs) {
    return complex_numbers::Complex(lhs, 0.0) + rhs;
}
inline complex_numbers::Complex operator-(complex_numbers::float_alias lhs, const complex_numbers::Complex& rhs) {
    return complex_numbers::Complex(lhs, 0.0) - rhs;
}
inline complex_numbers::Complex operator*(complex_numbers::float_alias lhs, const complex_numbers::Complex& rhs) {
    return complex_numbers::Complex(lhs, 0.0) * rhs;
}
inline complex_numbers::Complex operator/(complex_numbers::float_alias lhs, const complex_numbers::Complex& rhs) {
    // (a + 0i) / (c + di) = (a * c + 0 * d) / (c^2 + d^2) + (0 * c - a * d) / (c^2 + d^2) * i
    complex_numbers::float_alias denom = (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag());
    return complex_numbers::Complex(
        (lhs * rhs.real()) / denom,
        ((-lhs) * rhs.imag()) / denom
    );
}

#endif  // COMPLEX_NUMBERS_H
