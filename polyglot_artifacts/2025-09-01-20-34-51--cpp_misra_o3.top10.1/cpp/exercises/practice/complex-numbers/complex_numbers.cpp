#include "complex_numbers.h"

#include <stdexcept>

namespace complex_numbers {




/* Arithmetic operators */

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex{ (lhs.real() + rhs.real()), (lhs.imag() + rhs.imag()) };
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex{ (lhs.real() - rhs.real()), (lhs.imag() - rhs.imag()) };
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    return Complex{
        ((lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag())),
        ((lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag()))
    };
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    const double divisor{ (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()) };

    if (divisor == 0.0) {
        throw std::invalid_argument("division by zero in complex number division");
    }

    return Complex{
        (((lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag())) / divisor),
        (((lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag())) / divisor)
    };
}

/* Other operations */

Complex conj(const Complex& value) noexcept {
    return Complex{ value.real(), -(value.imag()) };
}

double abs(const Complex& value) noexcept {
    return std::sqrt((value.real() * value.real()) + (value.imag() * value.imag()));
}

Complex exp(const Complex& value) {
    const double exponent{ std::exp(value.real()) };

    return Complex{
        (exponent * std::cos(value.imag())),
        (exponent * std::sin(value.imag()))
    };
}

}  // namespace complex_numbers
