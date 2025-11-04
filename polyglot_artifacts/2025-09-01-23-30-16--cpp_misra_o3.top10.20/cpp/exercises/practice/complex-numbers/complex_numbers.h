#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H


namespace complex_numbers {

/*
 * Simple immutable complex number type that supports the basic
 * arithmetic operations as well as conjugate, absolute value
 * and exponent functions.
 *
 * Note: All binary arithmetic operators are implemented as free
 *       functions to comply with the MISRA “symmetrical operator”
 *       rule.
 */
class Complex final
{
public:
    constexpr Complex(double real_val = 0.0, double imag_val = 0.0) noexcept
        : m_real(real_val), m_imag(imag_val) {}

    [[nodiscard]] constexpr double real() const noexcept { return m_real; }
    [[nodiscard]] constexpr double imag() const noexcept { return m_imag; }

    [[nodiscard]] Complex  conj() const noexcept { return conjugate(); }
    [[nodiscard]] Complex  conjugate() const noexcept;
    [[nodiscard]] double   abs() const noexcept;
    [[nodiscard]] Complex  exp() const noexcept;

    /*  Symmetrical operators implemented as friends  */
    friend Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator/(const Complex& lhs, const Complex& rhs);

private:
    double m_real;
    double m_imag;
};

/*  Free-function API required by the exercise  */
Complex add(const Complex& lhs, const Complex& rhs) noexcept;
Complex sub(const Complex& lhs, const Complex& rhs) noexcept;
Complex mul(const Complex& lhs, const Complex& rhs) noexcept;
Complex div(const Complex& lhs, const Complex& rhs);
Complex conjugate(const Complex& value) noexcept;
double  abs(const Complex& value) noexcept;
Complex exp(const Complex& value) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
