#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

// Member function definitions



Complex Complex::operator/(const Complex &other) const {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    return {(real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom};
}

Complex &Complex::operator+=(const Complex &other) {
    real_ += other.real_;
    imag_ += other.imag_;
    return *this;
}

Complex &Complex::operator-=(const Complex &other) {
    real_ -= other.real_;
    imag_ -= other.imag_;
    return *this;
}

Complex &Complex::operator*=(const Complex &other) {
    double r = real_ * other.real_ - imag_ * other.imag_;
    double i = imag_ * other.real_ + real_ * other.imag_;
    real_ = r;
    imag_ = i;
    return *this;
}

Complex &Complex::operator/=(const Complex &other) {
    double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
    double r = (real_ * other.real_ + imag_ * other.imag_) / denom;
    double i = (imag_ * other.real_ - real_ * other.imag_) / denom;
    real_ = r;
    imag_ = i;
    return *this;
}

// Free function definitions
Complex conjugate(const Complex &z) {
    return z.conj();
}

double abs(const Complex &z) {
    return z.abs();
}

Complex exp(const Complex &z) {
    return z.exp();
}

}  // namespace complex_numbers

namespace complex_numbers {

Complex Complex::operator/(double value) const {
    return {real_ / value, imag_ / value};
}

}  // namespace complex_numbers
