#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

class Complex {
public:
    Complex(double realPart = 0.0, double imagPart = 0.0) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator/=(const Complex& rhs);

    Complex conj() const noexcept;
    Complex conjugate() const noexcept;
    double abs() const noexcept;
    Complex exp() const;

private:
    double m_real;
    double m_imag;
};

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, const Complex& rhs);

Complex exp(const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
