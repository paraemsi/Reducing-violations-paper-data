#include "complex_numbers.h"

namespace complex_numbers {

Complex::Complex(float_alias real_val, float_alias imag_val)
    : real_part(real_val), imag_part(imag_val) {}

float_alias Complex::real() const {
    return real_part;
}

float_alias Complex::imag() const {
    return imag_part;
}

Complex Complex::operator+(const Complex& rhs) const {
    return Complex((real_part + rhs.real_part), (imag_part + rhs.imag_part));
}

Complex Complex::operator+(float_alias rhs) const {
    return Complex((real_part + rhs), imag_part);
}

Complex Complex::operator-(const Complex& rhs) const {
    return Complex((real_part - rhs.real_part), (imag_part - rhs.imag_part));
}

Complex Complex::operator-(float_alias rhs) const {
    return Complex((real_part - rhs), imag_part);
}

Complex Complex::operator*(const Complex& rhs) const {
    float_alias real_res = ((real_part * rhs.real_part) - (imag_part * rhs.imag_part));
    float_alias imag_res = ((imag_part * rhs.real_part) + (real_part * rhs.imag_part));
    return Complex(real_res, imag_res);
}

Complex Complex::operator*(float_alias rhs) const {
    return Complex((real_part * rhs), (imag_part * rhs));
}

Complex Complex::operator/(const Complex& rhs) const {
    float_alias denom = ((rhs.real_part * rhs.real_part) + (rhs.imag_part * rhs.imag_part));
    float_alias real_res = (((real_part * rhs.real_part) + (imag_part * rhs.imag_part)) / denom);
    float_alias imag_res = (((imag_part * rhs.real_part) - (real_part * rhs.imag_part)) / denom);
    return Complex(real_res, imag_res);
}

Complex Complex::operator/(float_alias rhs) const {
    return Complex((real_part / rhs), (imag_part / rhs));
}

Complex Complex::conjugate() const {
    return Complex(real_part, (-imag_part));
}

Complex Complex::conj() const {
    return conjugate();
}

float_alias Complex::abs() const {
    return std::sqrt(((real_part * real_part) + (imag_part * imag_part)));
}

Complex Complex::exp() const {
    float_alias exp_real = std::exp(real_part);
    float_alias cos_imag = std::cos(imag_part);
    float_alias sin_imag = std::sin(imag_part);
    return Complex((exp_real * cos_imag), (exp_real * sin_imag));
}

}  // namespace complex_numbers
