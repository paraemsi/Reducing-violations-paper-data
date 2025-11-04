#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>

namespace complex_numbers {

/* Simple complex-number implementation compliant with MISRA C++ rules */
class Complex
{
public:
    /* Constructors */
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : m_real(real), m_imag(imag) {}

    /* Accessors */
    double real() const noexcept;
    double imag() const noexcept;

    /* Compound assignment operators */
    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

    /* Unary operations */
    Complex conjugate() const noexcept;
    Complex conj()      const noexcept;      /* alias expected by tests   */
    double  abs()       const noexcept;
    Complex exp()       const;               /* member exponential        */

private:
    double m_real;
    double m_imag;
};

/* Binary arithmetic operators implemented via compound assignments */
Complex operator+(Complex lhs, const Complex& rhs) noexcept;
Complex operator-(Complex lhs, const Complex& rhs) noexcept;
Complex operator*(Complex lhs, const Complex& rhs) noexcept;
Complex operator/(Complex lhs, const Complex& rhs);

/* Exponential function: e^(a + i b) */
Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
