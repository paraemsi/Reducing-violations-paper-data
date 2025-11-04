#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag)
    : real_(real), imag_(imag) {}

double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

Complex Complex::operator+(const Complex& other) const {
    return {real_ + other.real_, imag_ + other.imag_};
}

Complex Complex::operator-(const Complex& other) const {
    return {real_ - other.real_, imag_ - other.imag_};
}

Complex Complex::operator*(const Complex& other) const {
    return {real_ * other.real_ - imag_ * other.imag_,
            imag_ * other.real_ + real_ * other.imag_};
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return {(real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom};
}

Complex Complex::conj() const {
    return {real_, -imag_};
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    double exp_real = std::exp(real_);
    return {exp_real * std::cos(imag_), exp_real * std::sin(imag_)};
}

// scalar operations -------------------------------------------------

Complex Complex::operator+(double rhs) const {
    return {real_ + rhs, imag_};
}

Complex Complex::operator-(double rhs) const {
    return {real_ - rhs, imag_};
}

Complex Complex::operator*(double rhs) const {
    return {real_ * rhs, imag_ * rhs};
}

Complex Complex::operator/(double rhs) const {
    return {real_ / rhs, imag_ / rhs};
}

// comparison --------------------------------------------------------

bool Complex::operator==(const Complex& other) const {
    const double epsilon = 1e-12;
    return std::fabs(real_ - other.real_) < epsilon &&
           std::fabs(imag_ - other.imag_) < epsilon;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// free (friend) scalar functions ------------------------------------

Complex operator+(double lhs, const Complex& rhs) {
    return {lhs + rhs.real_, rhs.imag_};
}

Complex operator-(double lhs, const Complex& rhs) {
    return {lhs - rhs.real_, -rhs.imag_};
}

Complex operator*(double lhs, const Complex& rhs) {
    return {lhs * rhs.real_, lhs * rhs.imag_};
}

Complex operator/(double lhs, const Complex& rhs) {
    double denom = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
    return {(lhs * rhs.real_) / denom, (-lhs * rhs.imag_) / denom};
}

// (removed free Complex-Complex operator overloads to avoid ambiguity)

// free operations ---------------------------------------------------

Complex conj(const Complex& z) {
    return z.conj();
}

double abs(const Complex& z) {
    return z.abs();
}

Complex exp(const Complex& z) {
    return z.exp();
}

}  // namespace complex_numbers
