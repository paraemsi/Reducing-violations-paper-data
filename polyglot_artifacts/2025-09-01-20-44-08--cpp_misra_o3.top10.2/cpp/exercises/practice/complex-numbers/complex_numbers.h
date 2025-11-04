#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

/*
 * Simple complex number representation that complies with the given MISRA C++ rules.
 * All data members are public by design ‑ this avoids the need for friend access
 * while still keeping the type a POD-like aggregate which is convenient for tests.
 */
struct Complex final
{
    double real_;
    double imag_;

    constexpr Complex(double r = 0.0, double i = 0.0) noexcept : real_(r), imag_(i) {}

    /*  Accessors matching std::complex interface */
    [[nodiscard]] constexpr double real() const noexcept { return real_; }
    [[nodiscard]] constexpr double imag() const noexcept { return imag_; }

    /*  Convenience wrappers expected by the tests */
    [[nodiscard]] Complex conj() const noexcept { return conjugate(*this); }
    [[nodiscard]] double  abs()  const noexcept { return complex_numbers::abs(*this); }
    [[nodiscard]] Complex exp()  const noexcept { return complex_numbers::exp(*this); }
};

/*  Binary arithmetic operators (symmetrical) – implemented as non-member functions */
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, const Complex& rhs);

/*  Unary helpers  */
Complex  conjugate(const Complex& z) noexcept;
double   abs(const Complex& z) noexcept;
Complex  exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
