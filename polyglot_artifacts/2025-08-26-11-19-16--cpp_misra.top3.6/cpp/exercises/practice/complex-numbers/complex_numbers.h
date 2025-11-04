#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

using float_alias = double;

class Complex {
public:
    Complex(float_alias real, float_alias imag);

    float_alias real(void) const;
    float_alias imag(void) const;

    Complex operator+(Complex const& other) const;
    Complex operator-(Complex const& other) const;
    Complex operator*(Complex const& other) const;
    Complex operator/(Complex const& other) const;

    Complex conj(void) const;
    float_alias abs(void) const;
    Complex exp(void) const;

    // Scalar overloads
    Complex operator+(float_alias rhs) const;
    Complex operator-(float_alias rhs) const;
    Complex operator*(float_alias rhs) const;
    Complex operator/(float_alias rhs) const;

    // Data members must be in the public/private section of the class
private:
    float_alias m_real;
    float_alias m_imag;
};

// Non-member scalar overloads must be declared outside the class but inside the namespace
Complex operator+(float_alias lhs, Complex const& rhs);
Complex operator-(float_alias lhs, Complex const& rhs);
Complex operator*(float_alias lhs, Complex const& rhs);
Complex operator/(float_alias lhs, Complex const& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
