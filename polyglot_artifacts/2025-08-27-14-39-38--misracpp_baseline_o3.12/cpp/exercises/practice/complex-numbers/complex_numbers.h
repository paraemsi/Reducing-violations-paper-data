#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    constexpr Complex(double real_part = 0.0, double imag_part = 0.0)
        : m_real(real_part), m_imag(imag_part) {}

    // Accessors
    constexpr double real() const { return m_real; }
    constexpr double imag() const { return m_imag; }

    // Arithmetic operators
    constexpr Complex operator+(const Complex& other) const {
        return {m_real + other.m_real, m_imag + other.m_imag};
    }

    constexpr Complex operator-(const Complex& other) const {
        return {m_real - other.m_real, m_imag - other.m_imag};
    }

    constexpr Complex operator*(const Complex& other) const {
        return {m_real * other.m_real - m_imag * other.m_imag,
                m_imag * other.m_real + m_real * other.m_imag};
    }

    Complex operator/(const Complex& other) const;

    // Unary minus
    constexpr Complex operator-() const { return {-m_real, -m_imag}; }

    // Comparison (with tolerance)
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const { return !(*this == other); }

    // Additional operations
    constexpr Complex conjugate() const { return {m_real, -m_imag}; }
    // Alias expected by tests
    constexpr Complex conj() const { return conjugate(); }
    double abs() const;
    Complex exp() const;

private:
    double m_real;
    double m_imag;
    static constexpr double kEpsilon = 1e-12;
};

// Non-member operations (wrapper helpers)

// Complex with scalar (double)
inline constexpr Complex operator+(const Complex& lhs, double rhs) {
    return {lhs.real() + rhs, lhs.imag()};
}
inline constexpr Complex operator+(double lhs, const Complex& rhs) {
    return {lhs + rhs.real(), rhs.imag()};
}

inline constexpr Complex operator-(const Complex& lhs, double rhs) {
    return {lhs.real() - rhs, lhs.imag()};
}
inline constexpr Complex operator-(double lhs, const Complex& rhs) {
    return {lhs - rhs.real(), -rhs.imag()};
}

inline constexpr Complex operator*(const Complex& lhs, double rhs) {
    return {lhs.real() * rhs, lhs.imag() * rhs};
}
inline constexpr Complex operator*(double lhs, const Complex& rhs) {
    return {lhs * rhs.real(), lhs * rhs.imag()};
}

inline constexpr Complex operator/(const Complex& lhs, double rhs) {
    return {lhs.real() / rhs, lhs.imag() / rhs};
}
inline constexpr Complex operator/(double lhs, const Complex& rhs) {
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return {lhs * rhs.real() / denom, -lhs * rhs.imag() / denom};
}

// Utility free functions
inline double abs(const Complex& c) { return c.abs(); }
inline constexpr Complex conj(const Complex& c) { return c.conjugate(); }
inline Complex exp(const Complex& c) { return c.exp(); }

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
