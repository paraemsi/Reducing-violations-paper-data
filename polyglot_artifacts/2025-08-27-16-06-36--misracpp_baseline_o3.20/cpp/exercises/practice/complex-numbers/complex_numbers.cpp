#include "complex_numbers.h"
#include <cmath>
#include <stdexcept>

namespace complex_numbers {

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
    const double real_tmp = real_ * other.real_ - imag_ * other.imag_;
    imag_ = imag_ * other.real_ + real_ * other.imag_;
    real_ = real_tmp;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    const double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    if (denominator == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }
    const double real_tmp =
        (real_ * other.real_ + imag_ * other.imag_) / denominator;
    imag_ = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    real_ = real_tmp;
    return *this;
}

/* Free-standing arithmetic operators */

Complex operator+(Complex lhs, const Complex& rhs) noexcept {
    return lhs += rhs;
}

Complex operator-(Complex lhs, const Complex& rhs) noexcept {
    return lhs -= rhs;
}

Complex operator*(Complex lhs, const Complex& rhs) noexcept {
    return lhs *= rhs;
}

Complex operator/(Complex lhs, const Complex& rhs) {
    return lhs /= rhs;
}

Complex Complex::operator-() const noexcept {
    return Complex{-real_, -imag_};
}

/* Comparison operators */

bool operator==(const Complex& lhs, const Complex& rhs) noexcept {
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

bool operator!=(const Complex& lhs, const Complex& rhs) noexcept {
    return !(lhs == rhs);
}

/* Member wrappers for helper operations */

double Complex::abs() const noexcept {
    return complex_numbers::abs(*this);
}

Complex Complex::conj() const noexcept {
    return complex_numbers::conjugate(*this);
}

Complex Complex::exp() const noexcept {
    return complex_numbers::exp(*this);
}

/* Helper operations */

Complex conjugate(const Complex& z) noexcept {
    return Complex{z.real(), -z.imag()};
}

Complex conj(const Complex& z) noexcept {
    return conjugate(z);
}

double abs(const Complex& z) noexcept {
    return std::sqrt(z.real() * z.real() + z.imag() * z.imag());
}

Complex exp(const Complex& z) noexcept {
    const double e_to_a = std::exp(z.real());
    return Complex{e_to_a * std::cos(z.imag()),
                   e_to_a * std::sin(z.imag())};
}

}  // namespace complex_numbers
