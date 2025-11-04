#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

/*
 * A lightweight complex number implementation that provides the minimal
 * operations required by the exercise.  All symmetric operators are
 * implemented as non-member functions to satisfy MISRA C++ guidelines.
 */
class Complex final
{
public:
    constexpr Complex(double realVal = 0.0, double imagVal = 0.0) noexcept
        : real_{realVal}, imag_{imagVal}
    {
    }

    [[nodiscard]] constexpr double real() const noexcept
    {
        return real_;
    }

    [[nodiscard]] constexpr double imag() const noexcept
    {
        return imag_;
    }

    /* Aliases / helpers -------------------------------------------------- */
    [[nodiscard]] constexpr Complex conj() const noexcept
    {
        return conjugate();
    }

    /* Non-static member wrappers that forward to the free functions. */
    [[nodiscard]] double abs() const noexcept;
    [[nodiscard]] Complex exp() const;

    [[nodiscard]] constexpr Complex conjugate() const noexcept
    {
        return Complex(real_, (-imag_));
    }

private:
    double real_;
    double imag_;
};

/* --- free functions / operators --------------------------------------- */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

[[nodiscard]] double   abs(const Complex& z) noexcept;
[[nodiscard]] Complex  exp(const Complex& z);
[[nodiscard]] Complex  conjugate(const Complex& z) noexcept;
[[nodiscard]] Complex  conj(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
