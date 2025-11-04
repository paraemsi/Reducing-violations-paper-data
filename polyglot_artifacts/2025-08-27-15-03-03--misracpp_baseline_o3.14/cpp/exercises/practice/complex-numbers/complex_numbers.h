#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <stdexcept>
#include <ostream>

namespace complex_numbers {

class Complex {
public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : re_{real}, im_{imag} {}

    constexpr double real() const noexcept { return re_; }
    constexpr double imag() const noexcept { return im_; }

    // Conjugate
    constexpr Complex conj() const noexcept { return {re_, -im_}; }

    // Compound assignment operators
    Complex& operator+=(const Complex& other) noexcept {
        re_ += other.re_;
        im_ += other.im_;
        return *this;
    }

    Complex& operator-=(const Complex& other) noexcept {
        re_ -= other.re_;
        im_ -= other.im_;
        return *this;
    }

    Complex& operator*=(const Complex& other) noexcept {
        double r = re_ * other.re_ - im_ * other.im_;
        double i = im_ * other.re_ + re_ * other.im_;
        re_ = r;
        im_ = i;
        return *this;
    }

    Complex& operator/=(const Complex& other);  // Defined in .cpp

    // Binary arithmetic operators
    inline Complex operator+(const Complex& other) const noexcept {
        Complex result = *this;
        result += other;
        return result;
    }

    inline Complex operator-(const Complex& other) const noexcept {
        Complex result = *this;
        result -= other;
        return result;
    }

    inline Complex operator*(const Complex& other) const noexcept {
        Complex result = *this;
        result *= other;
        return result;
    }

    inline Complex operator/(const Complex& other) const {
        Complex result = *this;
        result /= other;
        return result;
    }

    // Magnitude of the complex number
    inline double abs() const noexcept {
        return std::sqrt(re_ * re_ + im_ * im_);
    }

    // Exponential of a complex number
    inline Complex exp() const {
        double exp_real = std::exp(re_);
        return {exp_real * std::cos(im_), exp_real * std::sin(im_)};
    }

private:
    double re_;
    double im_;
};





 // Unary operators
inline constexpr Complex operator+(const Complex& z) noexcept {
    return z;
}

inline constexpr Complex operator-(const Complex& z) noexcept {
    return {-z.real(), -z.imag()};
}

// Mixed-type operators
inline Complex operator+(double lhs, const Complex& rhs) noexcept {
    return {lhs + rhs.real(), rhs.imag()};
}

inline Complex operator+(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() + rhs, lhs.imag()};
}

inline Complex operator*(double lhs, const Complex& rhs) noexcept {
    return {lhs * rhs.real(), lhs * rhs.imag()};
}

/// Multiply complex by real (rhs)
inline Complex operator*(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() * rhs, lhs.imag() * rhs};
}

/// Subtract a complex number from a real number.
inline Complex operator-(double lhs, const Complex& rhs) noexcept {
    return {lhs - rhs.real(), -rhs.imag()};
}

/// Subtract a real number from a complex number.
inline Complex operator-(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() - rhs, lhs.imag()};
}

/// Divide a real number by a complex number.
inline Complex operator/(double lhs, const Complex& rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    if (denom == 0.0) {
        throw std::invalid_argument("Division by zero complex number");
    }
    double real_part = lhs * rhs.real() / denom;
    double imag_part = -lhs * rhs.imag() / denom;
    return {real_part, imag_part};
}

/// Divide a complex number by a real number.
inline Complex operator/(const Complex& lhs, double rhs) {
    if (rhs == 0.0) {
        throw std::invalid_argument("Division by zero scalar");
    }
    return {lhs.real() / rhs, lhs.imag() / rhs};
}

// Equality comparison with tolerance to account for floating-point error
inline bool operator==(const Complex& lhs, const Complex& rhs) noexcept {
    constexpr double EPS = 1e-10;
    return std::abs(lhs.real() - rhs.real()) <= EPS &&
           std::abs(lhs.imag() - rhs.imag()) <= EPS;
}

// Stream insertion for easy debugging / Catch2 output
inline std::ostream& operator<<(std::ostream& os, const Complex& z) {
    os << '(' << z.real() << ',' << z.imag() << ')';
    return os;
}

inline bool operator!=(const Complex& lhs, const Complex& rhs) noexcept {
    return !(lhs == rhs);
}

// Other helper functions
inline double abs(const Complex& z) {
    return std::sqrt(z.real() * z.real() + z.imag() * z.imag());
}

inline Complex exp(const Complex& z) {
    double exp_real = std::exp(z.real());
    return {exp_real * std::cos(z.imag()), exp_real * std::sin(z.imag())};
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
