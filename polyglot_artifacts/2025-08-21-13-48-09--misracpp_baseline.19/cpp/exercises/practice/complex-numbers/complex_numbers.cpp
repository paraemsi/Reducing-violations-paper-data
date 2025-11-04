#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double r, double i) noexcept : real(r), imag(i) {}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const noexcept {
    return Complex(
        real * other.real - imag * other.imag,
        imag * other.real + real * other.imag
    );
}

Complex Complex::operator/(const Complex& other) const noexcept {
    double denom = other.real * other.real + other.imag * other.imag;
    return Complex(
        (real * other.real + imag * other.imag) / denom,
        (imag * other.real - real * other.imag) / denom
    );
}

Complex Complex::conjugate() const noexcept {
    return Complex(real, -imag);
}

Complex Complex::conj() const noexcept {
    return conjugate();
}

double Complex::abs() const noexcept {
    return std::sqrt(real * real + imag * imag);
}

Complex Complex::exp() const noexcept {
    // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
    double exp_real = std::exp(real);
    return Complex(
        exp_real * std::cos(imag),
        exp_real * std::sin(imag)
    );
}

    // Non-member operators for double op Complex
Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex(lhs + rhs.real, rhs.imag);
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex(lhs - rhs.real, -rhs.imag);
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex(lhs * rhs.real, lhs * rhs.imag);
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    double denom = rhs.real * rhs.real + rhs.imag * rhs.imag;
    return Complex(
        (lhs * rhs.real) / denom,
        (-lhs * rhs.imag) / denom
    );
}

}  // namespace complex_numbers
