#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex() noexcept : re_{0.0}, im_{0.0} {}
Complex::Complex(double real, double imag) noexcept : re_{real}, im_{imag} {}

double Complex::real() const noexcept {
    return re_;
}

double Complex::imag() const noexcept {
    return im_;
}

double Complex::imaginary() const noexcept {
    return im_;
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex{(re_ + other.re_), (im_ + other.im_)};
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex{(re_ - other.re_), (im_ - other.im_)};
}

Complex Complex::operator*(const Complex& other) const noexcept {
    const double a = re_;
    const double b = im_;
    const double c = other.re_;
    const double d = other.im_;
    return Complex{((a * c) - (b * d)), ((b * c) + (a * d))};
}

Complex Complex::operator/(const Complex& other) const noexcept {
    const double a = re_;
    const double b = im_;
    const double c = other.re_;
    const double d = other.im_;
    const double denom = ((c * c) + (d * d));
    return Complex{(((a * c) + (b * d)) / denom), (((b * c) - (a * d)) / denom)};
}

Complex Complex::conj() const noexcept {
    return Complex{re_, (-im_)};
}

double Complex::abs() const noexcept {
    return std::sqrt(((re_ * re_) + (im_ * im_)));
}

Complex Complex::exp() const noexcept {
    const double a = re_;
    const double b = im_;
    const double e_to_a = std::exp(a);
    return Complex{(e_to_a * std::cos(b)), (e_to_a * std::sin(b))};
}

double real(const Complex& z) noexcept {
    return z.real();
}

double imag(const Complex& z) noexcept {
    return z.imag();
}

Complex conj(const Complex& z) noexcept {
    return z.conj();
}

double abs(const Complex& z) noexcept {
    return z.abs();
}

Complex exp(const Complex& z) noexcept {
    return z.exp();
}

Complex operator+(const Complex& lhs, double rhs) noexcept {
    return Complex{(lhs.real() + rhs), lhs.imag()};
}

Complex operator-(const Complex& lhs, double rhs) noexcept {
    return Complex{(lhs.real() - rhs), lhs.imag()};
}

Complex operator*(const Complex& lhs, double rhs) noexcept {
    return Complex{(lhs.real() * rhs), (lhs.imag() * rhs)};
}

Complex operator/(const Complex& lhs, double rhs) noexcept {
    return Complex{(lhs.real() / rhs), (lhs.imag() / rhs)};
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex{(lhs + rhs.real()), rhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex{(lhs - rhs.real()), (-rhs.imag())};
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex{(lhs * rhs.real()), (lhs * rhs.imag())};
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    const double c = rhs.real();
    const double d = rhs.imag();
    const double denom = ((c * c) + (d * d));
    return Complex{((lhs * c) / denom), ((-lhs * d) / denom)};
}

}  // namespace complex_numbers
