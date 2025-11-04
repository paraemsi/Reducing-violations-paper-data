#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex
{
public:
    constexpr Complex(double realVal = 0.0, double imagVal = 0.0) noexcept
        : m_real(realVal), m_imag(imagVal)
    {
    }

    [[nodiscard]] constexpr double real() const noexcept
    {
        return m_real;
    }

    [[nodiscard]] constexpr double imag() const noexcept
    {
        return m_imag;
    }

    [[nodiscard]] constexpr Complex conjugate() const noexcept
    {
        return Complex(m_real, -m_imag);
    }

    /* Additional member helpers expected by tests */
    [[nodiscard]] double abs() const noexcept;
    [[nodiscard]] Complex conj() const noexcept;
    [[nodiscard]] Complex exp() const;

private:
    double m_real;
    double m_imag;
};

/* Symmetrical operators implemented as non-member functions */
[[nodiscard]] constexpr Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] constexpr Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] constexpr Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

/* Utility operations */
[[nodiscard]] double abs(const Complex& z) noexcept;
[[nodiscard]] Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
