#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>

namespace complex_numbers {

class Complex {
public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : m_real(real), m_imag(imag) {}

    [[nodiscard]] constexpr double real() const noexcept { return m_real; }
    [[nodiscard]] constexpr double imag() const noexcept { return m_imag; }

    [[nodiscard]] constexpr Complex conjugate() const noexcept
    {
        return Complex(m_real, (-m_imag));
    }

    // aliases expected by the exercise tests
    [[nodiscard]] Complex conj() const noexcept;   // Return the complex conjugate
    [[nodiscard]] Complex exp() const;             // Calculate e^z

    [[nodiscard]] double abs() const noexcept;

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

private:
    double m_real;
    double m_imag;
};

bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

Complex operator+(Complex lhs, const Complex& rhs) noexcept;
Complex operator-(Complex lhs, const Complex& rhs) noexcept;
Complex operator*(Complex lhs, const Complex& rhs) noexcept;
Complex operator/(Complex lhs, const Complex& rhs);

// operations mixing complex with real scalars
Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;

Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;

Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;

Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

Complex exp(const Complex& z);

// free-standing absolute value helper expected by some code
double abs(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
