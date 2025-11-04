#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : re_{real}, im_{imag} {}

    constexpr double real() const noexcept { return re_; }
    constexpr double imag() const noexcept { return im_; }

    constexpr Complex operator+(const Complex& other) const noexcept {
        return {re_ + other.re_, im_ + other.im_};
    }

    constexpr Complex operator-(const Complex& other) const noexcept {
        return {re_ - other.re_, im_ - other.im_};
    }

    // unary negation
    constexpr Complex operator-() const noexcept { return {-re_, -im_}; }

    constexpr Complex operator*(const Complex& other) const noexcept {
        return {re_ * other.re_ - im_ * other.im_,
                im_ * other.re_ + re_ * other.im_};
    }

    Complex operator/(const Complex& other) const;

    // compound assignment operators
    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator/=(const Complex& other);

    constexpr Complex conj() const noexcept { return {re_, -im_}; }

    double abs() const noexcept { return std::sqrt(re_ * re_ + im_ * im_); }

    Complex exp() const;

private:
    double re_;
    double im_;
};

 // scalar multiplication with real numbers
constexpr inline Complex operator*(const Complex& c, double scalar) noexcept {
    return {c.real() * scalar, c.imag() * scalar};
}
constexpr inline Complex operator*(double scalar, const Complex& c) noexcept {
    return c * scalar;
}

// division by a real scalar on the right-hand side
constexpr inline Complex operator/(const Complex& c, double scalar) noexcept {
    return {c.real() / scalar, c.imag() / scalar};
}

// arithmetic with real number on the right-hand side
constexpr inline Complex operator+(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() + rhs, lhs.imag()};
}
constexpr inline Complex operator-(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() - rhs, lhs.imag()};
}

// arithmetic with real number on the left-hand side
constexpr inline Complex operator+(double lhs, const Complex& rhs) noexcept {
    return {lhs + rhs.real(), rhs.imag()};
}

constexpr inline Complex operator-(double lhs, const Complex& rhs) noexcept {
    return {lhs - rhs.real(), -rhs.imag()};
}

constexpr inline Complex operator/(double lhs, const Complex& rhs) noexcept {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return {(lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom};
}

// equality operators
inline bool operator==(const Complex& lhs, const Complex& rhs) noexcept {
    constexpr double EPSILON = 1e-10;
    return std::abs(lhs.real() - rhs.real()) < EPSILON &&
           std::abs(lhs.imag() - rhs.imag()) < EPSILON;
}
inline bool operator!=(const Complex& lhs, const Complex& rhs) noexcept {
    return !(lhs == rhs);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
