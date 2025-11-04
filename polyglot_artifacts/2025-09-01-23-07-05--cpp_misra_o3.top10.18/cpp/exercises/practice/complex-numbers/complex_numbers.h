#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

/* A lightweight complex-number type without relying on <complex>.
 * Implements basic arithmetic, conjugate, magnitude, and exponent.
 * All symmetrical binary operators are provided as non-member friends
 * to satisfy the MISRA guideline about symmetrical operators. */
class Complex final
{
public:
    /* Construct zero */
    Complex() noexcept;

    /* Construct from real and imaginary parts */
    Complex(double realPart, double imagPart) noexcept;

    /* Accessors */
    double real() const noexcept;
    double imag() const noexcept;

    /* Conjugate (a - i·b) */
    Complex conjugate() const noexcept;

    /* Magnitude |z| */
    double abs() const noexcept;

    /* Squared magnitude |z|² */
    double abs2() const noexcept;

    /* Exponential e^(a + i·b) */
    Complex exp() const noexcept;

    /* Alias used by tests */
    Complex conj() const noexcept;

    /* Compound assignments (allowed as members) */
    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);   /* may throw on divide-by-zero */

    /* Compound assignments with scalar (double) */
    Complex& operator+=(double rhs) noexcept;
    Complex& operator-=(double rhs) noexcept;
    Complex& operator*=(double rhs) noexcept;
    Complex& operator/=(double rhs);           /* may throw on divide-by-zero */

    /* Friend free symmetrical operators */
    friend Complex operator+(Complex lhs, const Complex& rhs) noexcept;
    friend Complex operator-(Complex lhs, const Complex& rhs) noexcept;
    friend Complex operator*(Complex lhs, const Complex& rhs) noexcept;
    friend Complex operator/(Complex lhs, const Complex& rhs);

    /* Friend equality operators */
    friend bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
    friend bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

private:
    double m_real;
    double m_imag;
};

/* (Declarations for the symmetrical Complex-vs-Complex operators and the
 * equality operators are already provided via the friend declarations inside
 * the class above; repeating them here is redundant.) */

/* Mixed complex / scalar (double) arithmetic */
Complex operator+(Complex lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;

Complex operator-(Complex lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;

Complex operator*(Complex lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;

Complex operator/(Complex lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
