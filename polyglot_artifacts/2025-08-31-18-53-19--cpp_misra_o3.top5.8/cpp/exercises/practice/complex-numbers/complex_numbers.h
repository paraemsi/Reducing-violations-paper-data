#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>   // fixed-width integer types per MISRA
#include <cmath>     // forward declaration needs <cmath>

namespace complex_numbers {

class Complex final
{
public:
    /* Constructor */
    constexpr Complex(double real_value = 0.0, double imag_value = 0.0) noexcept
        : m_real(real_value), m_imag(imag_value) {}

    /* Accessors */
    [[nodiscard]] double real() const noexcept;
    [[nodiscard]] double imag() const noexcept;

    /* Arithmetic operators */
    [[nodiscard]] Complex operator+(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator-(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator*(const Complex& other) const noexcept;
    [[nodiscard]] Complex operator/(const Complex& other) const;

    /* Comparison operators */
    [[nodiscard]] bool operator==(const Complex& other) const noexcept;
    [[nodiscard]] bool operator!=(const Complex& other) const noexcept;

    /* Scalar multiplication */
    [[nodiscard]] Complex operator*(double scalar) const noexcept;

    /* Other operations */
    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] double  abs()  const noexcept;
    [[nodiscard]] Complex exp()  const;

private:
    double m_real;
    double m_imag;
};

Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs);

/* Free-function API expected by the tests */
[[nodiscard]] Complex add (const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex sub (const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex mul (const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex div (const Complex& lhs, const Complex& rhs);
[[nodiscard]] Complex conj(const Complex& value) noexcept;
[[nodiscard]] double  abs (const Complex& value) noexcept;
[[nodiscard]] Complex exp (const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
