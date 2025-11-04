#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_type = double;

class Complex {
public:
    Complex(float_type real_value, float_type imag_value);

    float_type real(void) const;
    float_type imag(void) const;

    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;
    Complex conj(void) const;
    float_type abs(void) const;
    Complex exp(void) const;

    // Arithmetic with real numbers
    Complex operator+(float_type rhs) const;
    Complex operator-(float_type rhs) const;
    Complex operator*(float_type rhs) const;
    Complex operator/(float_type rhs) const;

    // Rule of five: add defaulted destructor, copy/move constructor/assignment
    ~Complex(void) = default;
    Complex(const Complex& other) = default;
    Complex(Complex&&) = default;
    Complex& operator=(const Complex& other) = default;
    Complex& operator=(Complex&&) = default;

private:
    float_type m_real;
    float_type m_imag;
};

// Non-member operators for real op Complex
Complex operator+(float_type lhs, const Complex& rhs);
Complex operator-(float_type lhs, const Complex& rhs);
Complex operator*(float_type lhs, const Complex& rhs);
Complex operator/(float_type lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
