#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    double new_real = real_ * other.real_ - imag_ * other.imag_;
    double new_imag = imag_ * other.real_ + real_ * other.imag_;
    return Complex(new_real, new_imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    return Complex(new_real, new_imag);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    double exp_real = std::exp(real_);
    return Complex(exp_real * std::cos(imag_), exp_real * std::sin(imag_));
}

// Unary negation
Complex Complex::operator-() const {
    return Complex(-real_, -imag_);
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

Complex& Complex::operator*=(double num) {
    real_ *= num;
    imag_ *= num;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    double new_real = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double new_imag = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    real_ = new_real;
    imag_ = new_imag;
    return *this;
}

/* Scalar and mixed operations */

// Scalar multiplication (Complex * double)
Complex Complex::operator*(double num) const {
    return Complex(real_ * num, imag_ * num);
}

// Scalar addition (Complex + double)
Complex Complex::operator+(double num) const {
    return Complex(real_ + num, imag_);
}

// Scalar subtraction (Complex - double)
Complex Complex::operator-(double num) const {
    return Complex(real_ - num, imag_);
}

// Scalar division (Complex / double)
Complex Complex::operator/(double num) const {
    return Complex(real_ / num, imag_ / num);
}

/* Comparison operators */
bool Complex::operator==(const Complex& other) const {
    constexpr double kTolerance = 1e-10;
    return std::abs(real_ - other.real_) < kTolerance &&
           std::abs(imag_ - other.imag_) < kTolerance;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

/* Non-member scalar and mixed operations */
Complex operator*(double num, const Complex& other) {
    return other * num;
}

Complex operator+(double num, const Complex& other) {
    return Complex(num + other.real(), other.imag());
}

Complex operator-(double num, const Complex& other) {
    return Complex(num - other.real(), -other.imag());
}

Complex operator/(double num, const Complex& other) {
    double denom = other.real() * other.real() + other.imag() * other.imag();
    return Complex(num * other.real() / denom, -num * other.imag() / denom);
}

}  // namespace complex_numbers
