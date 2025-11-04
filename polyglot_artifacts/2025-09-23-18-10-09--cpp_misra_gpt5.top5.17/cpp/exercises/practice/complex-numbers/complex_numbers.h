#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>
#include <cmath>

namespace complex_numbers {

class Complex final {
public:
    Complex() noexcept;
    Complex(double real, double imag) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

    Complex conjugate() const noexcept;
    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

private:
    double re_;
    double im_;
};

Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

Complex conjugate(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
