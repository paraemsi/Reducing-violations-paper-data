#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

// <cstdint> not required: no fixed-width integer types used

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept;
    Complex(double real, double imag) noexcept;
    double real() const noexcept;
    double imag() const noexcept;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

private:
    double re_{0.0};
    double im_{0.0};
};

 // Scalar operations with double
Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

// Unary operators
Complex operator+(const Complex& value) noexcept;
Complex operator-(const Complex& value) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
