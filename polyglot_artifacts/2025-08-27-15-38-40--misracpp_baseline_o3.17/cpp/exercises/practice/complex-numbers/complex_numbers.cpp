#include "complex_numbers.h"

#include <cmath>

namespace complex_numbers {

Complex::Complex(double real, double imag) : re_(real), im_(imag) {}

double Complex::real() const { return re_; }
double Complex::imag() const { return im_; }

Complex& Complex::operator+=(const Complex& other) {
    re_ += other.re_;
    im_ += other.im_;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    re_ -= other.re_;
    im_ -= other.im_;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double new_re = re_ * other.re_ - im_ * other.im_;
    double new_im = im_ * other.re_ + re_ * other.im_;
    re_ = new_re;
    im_ = new_im;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    double denom = other.re_ * other.re_ + other.im_ * other.im_;
    double new_re = (re_ * other.re_ + im_ * other.im_) / denom;
    double new_im = (im_ * other.re_ - re_ * other.im_) / denom;
    re_ = new_re;
    im_ = new_im;
    return *this;
}

Complex& Complex::operator*=(double scalar) {
    re_ *= scalar;
    im_ *= scalar;
    return *this;
}

Complex Complex::operator*(double scalar) const {
    Complex result(*this);
    result *= scalar;
    return result;
}

Complex Complex::operator/(double scalar) const {
    return {re_ / scalar, im_ / scalar};
}

Complex Complex::operator+(double scalar) const {
    return {re_ + scalar, im_};
}

Complex Complex::operator-(double scalar) const {
    return {re_ - scalar, im_};
}

Complex Complex::conj() const {
    return {re_, -im_};
}

double Complex::abs() const {
    return std::sqrt(re_ * re_ + im_ * im_);
}

Complex Complex::exp() const {
    double e_to_a = std::exp(re_);
    return {e_to_a * std::cos(im_), e_to_a * std::sin(im_)};
}

// Non-member operators implemented via compound assignment operators
Complex operator+(Complex lhs, const Complex& rhs) { return lhs += rhs; }
Complex operator-(Complex lhs, const Complex& rhs) { return lhs -= rhs; }
Complex operator*(Complex lhs, const Complex& rhs) { return lhs *= rhs; }
Complex operator/(Complex lhs, const Complex& rhs) { return lhs /= rhs; }
Complex operator*(double lhs, const Complex& rhs) { return rhs * lhs; }
Complex operator+(double lhs, const Complex& rhs) {
    return {lhs + rhs.real(), rhs.imag()};
}
Complex operator-(double lhs, const Complex& rhs) {
    return {lhs - rhs.real(), -rhs.imag()};
}
Complex operator/(double lhs, const Complex& rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return {lhs * rhs.real() / denom, -lhs * rhs.imag() / denom};
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

// Other operations
Complex conj(const Complex& value) {
    return {value.real(), -value.imag()};
}

double abs(const Complex& value) {
    return std::sqrt(value.real() * value.real() + value.imag() * value.imag());
}

Complex exp(const Complex& value) {
    double e_to_a = std::exp(value.real());
    return {e_to_a * std::cos(value.imag()), e_to_a * std::sin(value.imag())};
}

}  // namespace complex_numbers
