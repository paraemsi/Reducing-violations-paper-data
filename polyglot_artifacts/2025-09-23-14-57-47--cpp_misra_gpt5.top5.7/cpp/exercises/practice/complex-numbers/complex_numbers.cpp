#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) noexcept
    : re_(real), im_(imag) {}

double Complex::real() const noexcept {
    return re_;
}

double Complex::imag() const noexcept {
    return im_;
}

Complex Complex::operator+(const Complex& other) const noexcept {
    return Complex((re_ + other.re_), (im_ + other.im_));
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return Complex((re_ - other.re_), (im_ - other.im_));
}

Complex Complex::operator*(const Complex& other) const noexcept {
    double const real_part = ((re_ * other.re_) - (im_ * other.im_));
    double const imag_part = ((im_ * other.re_) + (re_ * other.im_));
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const noexcept {
    double const denom = ((other.re_) * (other.re_)) + ((other.im_) * (other.im_));
    double const real_part = (((re_) * (other.re_)) + ((im_) * (other.im_))) / denom;
    double const imag_part = (((im_) * (other.re_)) - ((re_) * (other.im_))) / denom;
    return Complex(real_part, imag_part);
}

Complex Complex::operator+(double value) const noexcept {
    return Complex((re_ + value), im_);
}

Complex Complex::operator-(double value) const noexcept {
    return Complex((re_ - value), im_);
}

Complex Complex::operator*(double value) const noexcept {
    return Complex((re_ * value), (im_ * value));
}

Complex Complex::operator/(double value) const noexcept {
    return Complex((re_ / value), (im_ / value));
}

Complex Complex::conjugate() const noexcept {
    return Complex(re_, (-im_));
}

Complex Complex::conj() const noexcept {
    return Complex(re_, (-im_));
}

double abs(const Complex& z) noexcept {
    return std::sqrt(((z.real() * z.real()) + (z.imag() * z.imag())));
}

Complex exp(const Complex& z) noexcept {
    double const ea = std::exp(z.real());
    double const cb = std::cos(z.imag());
    double const sb = std::sin(z.imag());
    return Complex((ea * cb), (ea * sb));
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs - rhs.real()), (-(rhs.imag())));
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) noexcept {
    double const c = rhs.real();
    double const d = rhs.imag();
    double const denom = ((c * c) + (d * d));
    double const real_part = ((lhs * c) / denom);
    double const imag_part = (((-lhs) * d) / denom);
    return Complex(real_part, imag_part);
}

}  // namespace complex_numbers
