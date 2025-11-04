#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

class Complex {
public:
    constexpr Complex(double realValue = 0.0, double imagValue = 0.0) noexcept
        : m_real(realValue), m_imag(imagValue) {}

    constexpr double real() const noexcept { return m_real; }
    constexpr double imag() const noexcept { return m_imag; }

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

    constexpr Complex operator+() const noexcept { return *this; }
    constexpr Complex operator-() const noexcept { return Complex((-m_real), (-m_imag)); }

    /* Additional utility member functions */
    constexpr Complex conj() const noexcept { return complex_numbers::conj(*this); }
    inline double abs() const noexcept { return complex_numbers::abs(*this); }
    Complex exp() const;

private:
    double m_real;
    double m_imag;
};

// Free functions
constexpr Complex conj(const Complex& z) noexcept
{
    return Complex(z.real(), (-z.imag()));
}

inline double abs(const Complex& z) noexcept
{
    return std::sqrt((z.real() * z.real()) + (z.imag() * z.imag()));
}

Complex exp(const Complex& z);

// Non-member operators
inline Complex operator+(Complex lhs, const Complex& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

inline Complex operator-(Complex lhs, const Complex& rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

inline Complex operator*(Complex lhs, const Complex& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

inline Complex operator/(Complex lhs, const Complex& rhs)
{
    lhs /= rhs;
    return lhs;
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
