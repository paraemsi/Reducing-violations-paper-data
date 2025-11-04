#include "complex_numbers.h"

namespace complex_numbers {

namespace {
constexpr double kEpsilon = 1e-10;
}  // namespace

// ----- member arithmetic -----
Complex Complex::operator+(const Complex& other) const noexcept {
    return {re_ + other.re_, im_ + other.im_};
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return {re_ - other.re_, im_ - other.im_};
}

Complex Complex::operator*(const Complex& other) const noexcept {
    return {re_ * other.re_ - im_ * other.im_,
            im_ * other.re_ + re_ * other.im_};
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = other.re_ * other.re_ + other.im_ * other.im_;
    return {(re_ * other.re_ + im_ * other.im_) / denom,
            (im_ * other.re_ - re_ * other.im_) / denom};
}

// ----- scalar arithmetic -----
Complex Complex::operator*(double scalar) const noexcept {
    return {re_ * scalar, im_ * scalar};
}

Complex Complex::operator/(double scalar) const {
    return {re_ / scalar, im_ / scalar};
}

// Addition / subtraction with scalar
Complex Complex::operator+(double scalar) const noexcept {
    return {re_ + scalar, im_};
}

Complex Complex::operator-(double scalar) const noexcept {
    return {re_ - scalar, im_};
}

// ----- unary operations -----
Complex Complex::conj() const noexcept {
    return {re_, -im_};
}

double Complex::abs() const noexcept {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    const double exp_re = std::exp(re_);
    return {exp_re * std::cos(im_), exp_re * std::sin(im_)};
}

// ----- equality -----
bool Complex::operator==(const Complex& other) const noexcept {
    return std::abs(re_ - other.re_) <= kEpsilon &&
           std::abs(im_ - other.im_) <= kEpsilon;
}

// ----- non-member scalar multiplication -----
Complex operator*(double scalar, const Complex& z) noexcept {
    return z * scalar;
}

Complex operator+(double scalar, const Complex& z) noexcept {
    return {scalar + z.real(), z.imag()};
}

Complex operator-(double scalar, const Complex& z) noexcept {
    return {scalar - z.real(), -z.imag()};
}

Complex operator/(double scalar, const Complex& z) {
    const double denom = z.real() * z.real() + z.imag() * z.imag();
    return {(scalar * z.real()) / denom,
            (-scalar * z.imag()) / denom};
}

}  // namespace complex_numbers
