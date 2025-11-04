#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex
{
public:
    Complex(double real_val = 0.0, double imag_val = 0.0) noexcept;

    [[nodiscard]]
    double real() const noexcept;

    [[nodiscard]]
    double imag() const noexcept;

    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator/=(const Complex& other);

    [[nodiscard]]
    Complex conjugate() const noexcept;

    [[nodiscard]]
    double abs() const noexcept;

    [[nodiscard]]
    Complex conj() const noexcept;

    [[nodiscard]]
    Complex exp() const;

private:
    double m_real;
    double m_imag;
};

/* Symmetrical (free) operators */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

/* Helper functions */
[[nodiscard]] Complex conj(const Complex& z) noexcept;
[[nodiscard]] double  abs(const Complex& z) noexcept;
[[nodiscard]] Complex exp(const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
