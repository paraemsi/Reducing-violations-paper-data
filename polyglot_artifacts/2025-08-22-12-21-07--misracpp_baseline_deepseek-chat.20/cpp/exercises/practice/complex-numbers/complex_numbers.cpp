#include "complex_numbers.h"
#include <cmath>
#include <limits>

namespace complex_numbers {

Complex::Complex(double real, double imag) : real_(real), imag_(imag) {}

double Complex::real() const {
    return real_;
}

double Complex::imag() const {
    return imag_;
}

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    // e^(a + bi) = e^a * (cos(b) + i*sin(b))
    double exp_real = std::exp(real_) * std::cos(imag_);
    double exp_imag = std::exp(real_) * std::sin(imag_);
    return Complex(exp_real, exp_imag);
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    double result_real = real_ * other.real_ - imag_ * other.imag_;
    double result_imag = imag_ * other.real_ + real_ * other.imag_;
    return Complex(result_real, result_imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    if (denominator == 0.0) {
        return Complex(
            std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity()
        );
    }
    double result_real = (real_ * other.real_ + imag_ * other.imag_) / denominator;
    double result_imag = (imag_ * other.real_ - real_ * other.imag_) / denominator;
    return Complex(result_real, result_imag);
}


}  // namespace complex_numbers
