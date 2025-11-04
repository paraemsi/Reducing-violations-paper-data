#include "complex_numbers.h"

#include <cmath>
#include <ostream>

namespace complex_numbers {

Complex::Complex(double real, double imag)
    : real_(real), imag_(imag) {}

double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

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

Complex& Complex::operator*=(double scalar) {
    real_ *= scalar;
    imag_ *= scalar;
    return *this;
}

Complex& Complex::operator/=(double scalar) {
    real_ /= scalar;
    imag_ /= scalar;
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

Complex Complex::operator-() const {
    return Complex(-real_, -imag_);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::exp() const {
    return complex_numbers::exp(*this);
}

Complex exp(const Complex& z) {
    double magnitude = std::exp(z.real());
    return Complex(magnitude * std::cos(z.imag()),
                   magnitude * std::sin(z.imag()));
}

Complex operator+(Complex lhs, const Complex& rhs) {
    lhs += rhs;
    return lhs;
}

Complex operator+(Complex lhs, double rhs) {
    lhs += Complex(rhs, 0.0);
    return lhs;
}

Complex operator+(double lhs, Complex rhs) {
    rhs += Complex(lhs, 0.0);
    return rhs;
}

Complex operator*(Complex lhs, double rhs) {
    lhs *= rhs;
    return lhs;
}

Complex operator*(double lhs, Complex rhs) {
    rhs *= lhs;
    return rhs;
}

Complex operator/(Complex lhs, double rhs) {
    lhs /= rhs;
    return lhs;
}

Complex operator/(double lhs, Complex rhs) {
    return Complex(lhs, 0.0) / rhs;
}

Complex operator-(Complex lhs, const Complex& rhs) {
    lhs -= rhs;
    return lhs;
}

Complex operator-(Complex lhs, double rhs) {
    lhs -= Complex(rhs, 0.0);
    return lhs;
}

Complex operator-(double lhs, Complex rhs) {
    rhs = Complex(lhs, 0.0) - rhs;
    return rhs;
}

Complex operator*(Complex lhs, const Complex& rhs) {
    lhs *= rhs;
    return lhs;
}

Complex operator/(Complex lhs, const Complex& rhs) {
    lhs /= rhs;
    return lhs;
}

Complex conj(const Complex& z) {
    return z.conj();
}

double abs(const Complex& z) {
    return z.abs();
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    constexpr double kEpsilon{1e-10};
    return std::fabs(lhs.real() - rhs.real()) < kEpsilon &&
           std::fabs(lhs.imag() - rhs.imag()) < kEpsilon;
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Complex& z) {
    os << '(' << z.real() << ',' << z.imag() << ')';
    return os;
}

}  // namespace complex_numbers
