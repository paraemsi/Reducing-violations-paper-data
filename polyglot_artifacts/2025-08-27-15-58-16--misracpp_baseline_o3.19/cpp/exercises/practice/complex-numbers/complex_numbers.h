#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;

public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : real_(real), imag_(imag) {}

    /* accessors */
    constexpr double real() const noexcept { return real_; }
    constexpr double imag() const noexcept { return imag_; }

    /* arithmetic operations */
    constexpr Complex operator+(const Complex& other) const noexcept {
        return {real_ + other.real_, imag_ + other.imag_};
    }

    constexpr Complex operator-(const Complex& other) const noexcept {
        return {real_ - other.real_, imag_ - other.imag_};
    }

    constexpr Complex operator*(const Complex& other) const noexcept {
        return {real_ * other.real_ - imag_ * other.imag_,
                imag_ * other.real_ + real_ * other.imag_};
    }

    /* unary plus and minus */
    constexpr Complex operator+() const noexcept { return *this; }
    constexpr Complex operator-() const noexcept { return {-real_, -imag_}; }

    Complex operator/(const Complex& other) const;

    /* unary operations */
    constexpr Complex conj() const noexcept { return {real_, -imag_}; }
    double abs() const noexcept;
    Complex exp() const;

    /* comparisons */
    constexpr bool operator==(const Complex& other) const noexcept {
        return real_ == other.real_ && imag_ == other.imag_;
    }
    constexpr bool operator!=(const Complex& other) const noexcept {
        return !(*this == other);
    }
};

/* free-function helpers to mirror member functions */
inline constexpr Complex conj(const Complex& c) noexcept { return c.conj(); }
inline double abs(const Complex& c) noexcept { return c.abs(); }
inline Complex exp(const Complex& c) { return c.exp(); }

/* Arithmetic with real numbers as the left-hand operand */
constexpr Complex operator+(double lhs, const Complex& rhs) noexcept {
    return {lhs + rhs.real(), rhs.imag()};
}

constexpr Complex operator-(double lhs, const Complex& rhs) noexcept {
    return {lhs - rhs.real(), -rhs.imag()};
}

constexpr Complex operator*(double lhs, const Complex& rhs) noexcept {
    return {lhs * rhs.real(), lhs * rhs.imag()};
}

constexpr Complex operator/(double lhs, const Complex& rhs) noexcept {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return {(lhs * rhs.real()) / denom, (-lhs * rhs.imag()) / denom};
}

/* Arithmetic with real numbers as the right-hand operand */
constexpr Complex operator+(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() + rhs, lhs.imag()};
}

constexpr Complex operator-(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() - rhs, lhs.imag()};
}

constexpr Complex operator*(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() * rhs, lhs.imag() * rhs};
}

constexpr Complex operator/(const Complex& lhs, double rhs) noexcept {
    return {lhs.real() / rhs, lhs.imag() / rhs};
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
