#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>

namespace complex_numbers {

class Complex final
{
public:
    /* Constructors */
    constexpr Complex() noexcept : m_real(0.0), m_imag(0.0) {}
    constexpr explicit Complex(double realPart,
                               double imagPart = 0.0) noexcept
        : m_real(realPart),
          m_imag(imagPart)
    {
    }

    /* Accessors */
    [[nodiscard]] constexpr double real() const noexcept { return m_real; }
    [[nodiscard]] constexpr double imag() const noexcept { return m_imag; }

    /* Operations */
    [[nodiscard]] constexpr Complex conjugate() const noexcept
    {
        return Complex(m_real, (0.0 - m_imag));
    }
    [[nodiscard]] constexpr Complex conj() const noexcept { return conjugate(); }

    [[nodiscard]] double abs() const noexcept;
    [[nodiscard]] Complex exp() const;

    /* Binary operators with Complex rhs */
    friend Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator/(const Complex& lhs, const Complex& rhs);

    /* Binary operators with scalar rhs (double) */
    friend Complex operator+(const Complex& lhs, double rhs) noexcept;
    friend Complex operator+(double lhs, const Complex& rhs) noexcept;

    friend Complex operator-(const Complex& lhs, double rhs) noexcept;
    friend Complex operator-(double lhs, const Complex& rhs) noexcept;

    friend Complex operator*(const Complex& lhs, double rhs) noexcept;
    friend Complex operator*(double lhs, const Complex& rhs) noexcept;

    friend Complex operator/(const Complex& lhs, double rhs) noexcept;
    friend Complex operator/(double lhs, const Complex& rhs);

private:
    double m_real;
    double m_imag;
};

Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
