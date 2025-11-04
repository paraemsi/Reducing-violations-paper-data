#include "complex_numbers.h"

#include <cmath>    // std::sqrt, std::exp, std::cos, std::sin
#include <stdexcept>

namespace complex_numbers {

/* ---- Arithmetic operators ------------------------------------------------ */

Complex Complex::operator+(const Complex& other) const noexcept {
    return {real_ + other.real_, imag_ + other.imag_};
}

Complex Complex::operator-(const Complex& other) const noexcept {
    return {real_ - other.real_, imag_ - other.imag_};
}

Complex Complex::operator*(const Complex& other) const noexcept {
    return {real_ * other.real_ - imag_ * other.imag_,
            imag_ * other.real_ + real_ * other.imag_};
}

Complex Complex::operator/(const Complex& other) const {
    const double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }
    return {(real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom};
}

/* ---- Scalar operations --------------------------------------------------- */

Complex Complex::operator*(double other) const noexcept {
    return {real_ * other, imag_ * other};
}

Complex Complex::operator/(double other) const {
    if (other == 0.0) {
        throw std::invalid_argument("Division by zero scalar value");
    }
    return {real_ / other, imag_ / other};
}

Complex Complex::operator+(double other) const noexcept {
    return {real_ + other, imag_};
}

Complex Complex::operator-(double other) const noexcept {
    return {real_ - other, imag_};
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    return rhs * lhs;
}

Complex operator+(double lhs, const Complex& rhs) noexcept {
    return {lhs + rhs.real(), rhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    return {lhs - rhs.real(), -rhs.imag()};
}

Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs) / rhs;
}

/* ---- Compound assignment operators -------------------------------------- */

Complex& Complex::operator+=(const Complex& other) noexcept {
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) noexcept {
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) noexcept {
    const double new_real = real_ * other.real_ - imag_ * other.imag_;
    const double new_imag = imag_ * other.real_ + real_ * other.imag_;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    const double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }
    const double new_real = (real_ * other.real_ + imag_ * other.imag_) / denom;
    const double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denom;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

/* ---- Comparison operators ----------------------------------------------- */

bool Complex::operator==(const Complex& other) const noexcept {
    return real_ == other.real_ && imag_ == other.imag_;
}

bool Complex::operator!=(const Complex& other) const noexcept {
    return !(*this == other);
}

/* ---- Derived operations --------------------------------------------------- */

Complex Complex::conj() const noexcept {
    return {real_, -imag_};
}

double Complex::abs() const noexcept {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    const double exp_real = std::exp(real_);
    return {exp_real * std::cos(imag_), exp_real * std::sin(imag_)};
}

}  // namespace complex_numbers
