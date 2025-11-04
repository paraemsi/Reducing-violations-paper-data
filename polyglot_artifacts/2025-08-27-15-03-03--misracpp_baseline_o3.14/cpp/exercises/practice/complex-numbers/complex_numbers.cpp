#include "complex_numbers.h"
#include <cmath>
#include <stdexcept>

namespace complex_numbers {

Complex& Complex::operator/=(const Complex& other) {
    double denom = other.real() * other.real() + other.imag() * other.imag();
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }
    double r = (re_ * other.real() + im_ * other.imag()) / denom;
    double i = (im_ * other.real() - re_ * other.imag()) / denom;
    re_ = r;
    im_ = i;
    return *this;
}

}  // namespace complex_numbers
