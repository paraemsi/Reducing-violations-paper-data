#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

/*
 * A lightweight complex‐number class that supports the basic arithmetic
 * operations together with conjugate, absolute value, and exponential.
 * All symmetrical operators are implemented as free (friend) functions
 * to comply with the MISRA “symmetrical operators” rule.
 */
class Complex {
public:
    Complex(double real_val = 0.0, double imag_val = 0.0) noexcept;

    [[nodiscard]] double real() const noexcept;
    [[nodiscard]] double imag() const noexcept;

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

    [[nodiscard]] Complex operator-() const noexcept;

    [[nodiscard]] Complex  conj() const noexcept;
    [[nodiscard]] double   abs()  const noexcept;
    [[nodiscard]] Complex  exp()  const;

private:
    double m_real;
    double m_imag;
};

/* ---- free symmetrical operators --------------------------------------- */
[[nodiscard]] Complex operator+(Complex lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(Complex lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(Complex lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(Complex lhs, const Complex& rhs);
[[nodiscard]] Complex operator*(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, double rhs);
[[nodiscard]] bool    operator==(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] bool    operator!=(const Complex& lhs, const Complex& rhs) noexcept;
/* convenience free functions that forward to the corresponding
 * member functions – useful for algorithm‐style calls               */
[[nodiscard]] Complex conj(const Complex& value) noexcept;
[[nodiscard]] double  abs(const Complex& value) noexcept;
[[nodiscard]] Complex exp(const Complex& value);

}   // namespace complex_numbers

#endif   // COMPLEX_NUMBERS_H
