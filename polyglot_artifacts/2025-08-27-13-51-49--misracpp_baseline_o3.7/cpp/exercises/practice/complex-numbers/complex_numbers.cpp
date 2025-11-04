#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

// Accessors
double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

// Addition
Complex Complex::operator+(const Complex& other) const {
    return {real_ + other.real_, imag_ + other.imag_};
}

// Subtraction
Complex Complex::operator-(const Complex& other) const {
    return {real_ - other.real_, imag_ - other.imag_};
}

// Multiplication
Complex Complex::operator*(const Complex& other) const {
    double new_real = real_ * other.real_ - imag_ * other.imag_;
    double new_imag = imag_ * other.real_ + real_ * other.imag_;
    return {new_real, new_imag};
}

// Division
Complex Complex::operator/(const Complex& other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denom;
    return {new_real, new_imag};
}

// Conjugate
Complex Complex::conj() const {
    return {real_, -imag_};
}

// Absolute value / magnitude
double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

// Exponential
Complex Complex::exp() const {
    double e_pow_real = std::exp(real_);
    double cos_imag   = std::cos(imag_);
    double sin_imag   = std::sin(imag_);
    return {e_pow_real * cos_imag, e_pow_real * sin_imag};
}

// Compound assignment operators
Complex& Complex::operator+=(const Complex& other) {
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double new_real = real_ * other.real_ - imag_ * other.imag_;
    double new_imag = imag_ * other.real_ + real_ * other.imag_;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denom;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

Complex operator+(const Complex& lhs, double rhs) {
    return {lhs.real() + rhs, lhs.imag()};
}

Complex operator+(double lhs, const Complex& rhs) {
    return rhs + lhs;
}

Complex operator-(const Complex& lhs, double rhs) {
    return {lhs.real() - rhs, lhs.imag()};
}

Complex operator-(double lhs, const Complex& rhs) {
    return {lhs - rhs.real(), -rhs.imag()};
}

Complex operator*(const Complex& lhs, double rhs) {
    return {lhs.real() * rhs, lhs.imag() * rhs};
}

Complex operator*(double lhs, const Complex& rhs) {
    return rhs * lhs;
}

Complex operator/(const Complex& lhs, double rhs) {
    return {lhs.real() / rhs, lhs.imag() / rhs};
}

Complex operator/(double lhs, const Complex& rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double new_real = lhs * rhs.real() / denom;
    double new_imag = -lhs * rhs.imag() / denom;
    return {new_real, new_imag};
}

// Comparison operators
bool operator==(const Complex& lhs, const Complex& rhs) {
    constexpr double kEpsilon = 1e-10;
    return std::abs(lhs.real() - rhs.real()) < kEpsilon &&
           std::abs(lhs.imag() - rhs.imag()) < kEpsilon;
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

}  // namespace complex_numbers
