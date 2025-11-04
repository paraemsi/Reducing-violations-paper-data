#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex
{
public:
    constexpr Complex(double r = 0.0, double i = 0.0) : m_real(r), m_imag(i) {}

    double real() const;
    double imag() const;

    // arithmetic operators
    Complex operator+(const Complex& rhs) const;
    Complex operator-(const Complex& rhs) const;
    Complex operator*(const Complex& rhs) const;
    Complex operator/(const Complex& rhs) const;

    // additional operations
    Complex conjugate() const;            // complex conjugate
    Complex conj() const { return conjugate(); } // alias used in tests
    double abs() const;                   // magnitude
    Complex exp() const;                  // e^(a + bi)

private:
    double m_real;
    double m_imag;
};


}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
