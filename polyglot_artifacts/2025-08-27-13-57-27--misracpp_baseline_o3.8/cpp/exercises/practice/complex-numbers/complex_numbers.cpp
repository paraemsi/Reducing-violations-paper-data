#include "complex_numbers.h"

#include <cmath>
#include <ostream>

namespace complex_numbers {

// Constructor
Complex::Complex(double r, double i) : real_{r}, imag_{i} {}

// Accessors
double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

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
    double r = real_ * other.real_ - imag_ * other.imag_;
    double i = imag_ * other.real_ + real_ * other.imag_;
    real_  = r;
    imag_  = i;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double r = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double i = (imag_ * other.real_ - real_ * other.imag_) / denom;
    real_  = r;
    imag_  = i;
    return *this;
}

// Unary operators
Complex Complex::operator+() const { return *this; }

Complex Complex::operator-() const { return Complex(-real_, -imag_); }

// Member utility operations
Complex Complex::conj() const { return Complex(real_, -imag_); }

double Complex::abs() const { return std::sqrt(real_ * real_ + imag_ * imag_); }

Complex Complex::exp() const {
    double ea = std::exp(real_);
    return Complex(ea * std::cos(imag_), ea * std::sin(imag_));
}

// Non-member arithmetic operators
Complex operator+(Complex lhs, const Complex& rhs) {
    lhs += rhs;
    return lhs;
}

Complex operator-(Complex lhs, const Complex& rhs) {
    lhs -= rhs;
    return lhs;
}

Complex operator*(Complex lhs, const Complex& rhs) {
    lhs *= rhs;
    return lhs;
}

// Division
Complex operator/(Complex lhs, const Complex& rhs) {
    lhs /= rhs;
    return lhs;
}

// Comparison operators (with small tolerance for floating-point error)
namespace {
constexpr double kEpsilon = 1e-10;
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    return std::fabs(lhs.real() - rhs.real()) < kEpsilon &&
           std::fabs(lhs.imag() - rhs.imag()) < kEpsilon;
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

// Scalar multiplication helpers
Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}

// Complex-scalar helpers
Complex operator+(Complex lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}

Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(Complex lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator/(Complex lhs, double rhs) {
    if (rhs == 0.0) {
        throw std::domain_error("division of complex by zero scalar");
    }
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

Complex operator/(double lhs, const Complex& rhs) {
    return Complex(lhs, 0.0) / rhs;
}

 // Conjugate
Complex conj(const Complex& c) {
    return c.conj();
}

// Absolute value
double abs(const Complex& c) {
    return c.abs();
}

// Exponential
Complex exp(const Complex& c) {
    return c.exp();
}

// Optional stream output
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real();
    if (c.imag() >= 0) {
        os << " + " << c.imag() << "i";
    } else {
        os << " - " << -c.imag() << "i";
    }
    return os;
}

}  // namespace complex_numbers
