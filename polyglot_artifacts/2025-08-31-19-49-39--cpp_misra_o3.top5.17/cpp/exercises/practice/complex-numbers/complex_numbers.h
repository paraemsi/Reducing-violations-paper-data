#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

class Complex final
{
public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : real_(real), imag_(imag) {}

    double real() const noexcept { return real_; }
    double imag() const noexcept { return imag_; }

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const;

    Complex conjugate() const noexcept;
    Complex conj() const noexcept { return conjugate(); }
    double abs() const noexcept;
    Complex exp() const;

private:
    double real_;
    double imag_;
};

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) ;

Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs) ;

Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
