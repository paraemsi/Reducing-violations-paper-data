#include "complex_numbers.h"
#include <limits>

namespace complex_numbers {

Complex Complex::operator+(const Complex& other) const noexcept {
    const double real_part{real_ + other.real_};
    const double imag_part{imag_ + other.imag_};
    return Complex(real_part, imag_part);
}

Complex Complex::operator-(const Complex& other) const noexcept {
    const double real_part{real_ - other.real_};
    const double imag_part{imag_ - other.imag_};
    return Complex(real_part, imag_part);
}

Complex Complex::operator*(const Complex& other) const noexcept {
    const double real_part{(real_ * other.real_) - (imag_ * other.imag_)};
    const double imag_part{(imag_ * other.real_) + (real_ * other.imag_)};
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex& other) const {
    const double denominator{(other.real_ * other.real_) + (other.imag_ * other.imag_)};

    if (denominator == 0.0) {
        // Division by zero – behaviour is undefined, but we return NaNs to indicate error
        return Complex(std::numeric_limits<double>::quiet_NaN(),
                       std::numeric_limits<double>::quiet_NaN());
    }

    const double real_part{((real_ * other.real_) + (imag_ * other.imag_)) / denominator};
    const double imag_part{((imag_ * other.real_) - (real_ * other.imag_)) / denominator};
    return Complex(real_part, imag_part);
}

Complex Complex::conj() const noexcept {
    return Complex(real_, -imag_);
}

double Complex::abs() const noexcept {
    return std::sqrt((real_ * real_) + (imag_ * imag_));
}

Complex Complex::exp() const {
    const double magnitude{std::exp(real_)};
    const double real_part{magnitude * std::cos(imag_)};
    const double imag_part{magnitude * std::sin(imag_)};
    return Complex(real_part, imag_part);
}

// ---------------------------------------------------------------------------
// Non-member arithmetic operators with a scalar on the LHS
// ---------------------------------------------------------------------------

Complex operator+(double lhs, const Complex& rhs) noexcept {
    const Complex lhs_c{lhs, 0.0};
    return lhs_c + rhs;
}

Complex operator-(double lhs, const Complex& rhs) noexcept {
    const Complex lhs_c{lhs, 0.0};
    return lhs_c - rhs;
}

Complex operator*(double lhs, const Complex& rhs) noexcept {
    const Complex lhs_c{lhs, 0.0};
    return lhs_c * rhs;
}

Complex operator/(double lhs, const Complex& rhs) {
    const Complex lhs_c{lhs, 0.0};
    return lhs_c / rhs;
}

}  // namespace complex_numbers
