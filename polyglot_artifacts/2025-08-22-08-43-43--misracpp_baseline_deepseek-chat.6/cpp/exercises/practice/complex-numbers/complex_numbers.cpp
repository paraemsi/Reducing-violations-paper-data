#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

double Complex::abs() const {
    return std::sqrt(real_ * real_ + imag_ * imag_);
}

Complex Complex::conj() const {
    return Complex(real_, -imag_);
}

Complex Complex::exp() const {
    // Using Euler's formula: e^(a + bi) = e^a * (cos(b) + i*sin(b))
    return Complex(std::exp(real_) * std::cos(imag_), 
                  std::exp(real_) * std::sin(imag_));
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real_ - other.real_, imag_ - other.imag_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real_ * other.real_ - imag_ * other.imag_,
                  imag_ * other.real_ + real_ * other.imag_);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
    return Complex((real_ * other.real_ + imag_ * other.imag_) / denominator,
                  (imag_ * other.real_ - real_ * other.imag_) / denominator);
}


}  // namespace complex_numbers
