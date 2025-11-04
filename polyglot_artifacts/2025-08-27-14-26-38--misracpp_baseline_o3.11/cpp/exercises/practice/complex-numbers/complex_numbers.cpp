#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex Complex::operator/(const Complex& other) const {
    double denom = other.real() * other.real() + other.imag() * other.imag();
    return {(real() * other.real() + imag() * other.imag()) / denom,
            (imag() * other.real() - real() * other.imag()) / denom};
}

Complex Complex::exp() const {
    double exp_real = std::exp(real());
    return {exp_real * std::cos(imag()), exp_real * std::sin(imag())};
}

Complex& Complex::operator+=(const Complex& other) noexcept {
    re_ += other.real();
    im_ += other.imag();
    return *this;
}

Complex& Complex::operator-=(const Complex& other) noexcept {
    re_ -= other.real();
    im_ -= other.imag();
    return *this;
}

Complex& Complex::operator*=(const Complex& other) noexcept {
    double new_re = re_ * other.real() - im_ * other.imag();
    double new_im = im_ * other.real() + re_ * other.imag();
    re_ = new_re;
    im_ = new_im;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denom = other.real() * other.real() + other.imag() * other.imag();
    double new_re = (re_ * other.real() + im_ * other.imag()) / denom;
    double new_im = (im_ * other.real() - re_ * other.imag()) / denom;
    re_ = new_re;
    im_ = new_im;
    return *this;
}

}  // namespace complex_numbers
