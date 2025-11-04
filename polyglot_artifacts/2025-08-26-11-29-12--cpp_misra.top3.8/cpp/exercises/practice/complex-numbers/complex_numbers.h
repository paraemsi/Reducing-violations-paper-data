#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex {
public:
    Complex(float_alias real_value, float_alias imag_value);

    float_alias real(void) const;
    float_alias imag(void) const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex operator+(float_alias value) const;
    Complex operator-(float_alias value) const;
    Complex operator*(float_alias value) const;
    Complex operator/(float_alias value) const;

    Complex conj(void) const;
    float_alias abs(void) const;
    Complex exp(void) const;

    // Rule of five: add defaulted destructor, copy/move constructor and assignment
    ~Complex(void) = default;
    Complex(const Complex&) = default;
    Complex(Complex&&) = default;
    Complex& operator=(const Complex&) = default;
    Complex& operator=(Complex&&) = default;

private:
    float_alias real_part;
    float_alias imag_part;
};

// Non-member operators for double op Complex
Complex operator+(float_alias lhs, const Complex& rhs);
Complex operator-(float_alias lhs, const Complex& rhs);
Complex operator*(float_alias lhs, const Complex& rhs);
Complex operator/(float_alias lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
