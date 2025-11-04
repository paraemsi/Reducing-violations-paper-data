#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

struct Complex {
private:
    double real_;
    double imag_;

public:
    constexpr Complex(double r = 0.0, double i = 0.0) : real_(r), imag_(i) {}

    // Accessors
    constexpr double real() const { return real_; }
    constexpr double imag() const { return imag_; }

    // Basic arithmetic operators
    constexpr Complex operator+(const Complex &other) const {
        return {real_ + other.real_, imag_ + other.imag_};
    }
    constexpr Complex operator-(const Complex &other) const {
        return {real_ - other.real_, imag_ - other.imag_};
    }
    constexpr Complex operator*(const Complex &other) const {
        return {real_ * other.real_ - imag_ * other.imag_,
                imag_ * other.real_ + real_ * other.imag_};
    }
    Complex operator/(const Complex &other) const;

    // Operations with a scalar real number
    constexpr Complex operator+(double value) const {
        return {real_ + value, imag_};
    }
    constexpr Complex operator-(double value) const {
        return {real_ - value, imag_};
    }
    constexpr Complex operator*(double value) const {
        return {real_ * value, imag_ * value};
    }
    Complex operator/(double value) const;

    // Compound assignment operators
    Complex &operator+=(const Complex &other);
    Complex &operator-=(const Complex &other);
    Complex &operator*=(const Complex &other);
    Complex &operator/=(const Complex &other);

    // Member utility functions
    // Return the complex conjugate of *this.
    constexpr Complex conj() const { return {real_, -imag_}; }

    // Return the magnitude (absolute value) of *this.
    double abs() const { return std::hypot(real_, imag_); }

    // Return e raised to the power of *this.
    Complex exp() const {
        double exp_real = std::exp(real_);
        return {exp_real * std::cos(imag_), exp_real * std::sin(imag_)};
    }
};

// Utility functions
Complex conjugate(const Complex &z);
double abs(const Complex &z);
Complex exp(const Complex &z);

// Free functions for operations with a scalar on the left-hand side
constexpr Complex operator+(double value, const Complex &z) {
    return z + value;
}
constexpr Complex operator-(double value, const Complex &z) {
    return {value - z.real(), -z.imag()};
}
constexpr Complex operator*(double value, const Complex &z) {
    return z * value;
}
inline Complex operator/(double value, const Complex &z) {
    double denom = z.real() * z.real() + z.imag() * z.imag();
    return {(value * z.real()) / denom, (-value * z.imag()) / denom};
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
