#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

 // <cstdint> not required; no integer types used.

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept;
    Complex(double real, double imag) noexcept;
    double real() const noexcept;
    double imag() const noexcept;
    double imaginary() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

private:
    double re_;
    double im_;
};

double real(const Complex& z) noexcept;
double imag(const Complex& z) noexcept;

Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs) noexcept;

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
