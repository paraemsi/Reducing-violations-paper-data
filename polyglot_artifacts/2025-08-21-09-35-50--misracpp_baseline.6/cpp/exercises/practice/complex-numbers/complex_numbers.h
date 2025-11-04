#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
public:
    Complex(double real, double imag) : real_(real), imag_(imag) {}

    double real() const { return real_; }
    double imag() const { return imag_; }

    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real_ * other.real_ - imag_ * other.imag_,
            imag_ * other.real_ + real_ * other.imag_
        );
    }

    Complex operator/(const Complex& other) const {
        double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
        return Complex(
            (real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom
        );
    }

    Complex conjugate() const {
        return Complex(real_, -imag_);
    }

    // Alias for conjugate to match test expectations
    Complex conj() const {
        return conjugate();
    }

    double abs() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }

    Complex exp() const {
        // e^(a + i*b) = e^a * (cos(b) + i*sin(b))
        double exp_real = std::exp(real_);
        return Complex(
            exp_real * std::cos(imag_),
            exp_real * std::sin(imag_)
        );
    }

private:
    double real_;
    double imag_;
};

// Non-member operator overloads for double on right
inline Complex operator+(const Complex& lhs, double rhs) {
    return Complex(lhs.real() + rhs, lhs.imag());
}
inline Complex operator-(const Complex& lhs, double rhs) {
    return Complex(lhs.real() - rhs, lhs.imag());
}
inline Complex operator*(const Complex& lhs, double rhs) {
    return Complex(lhs.real() * rhs, lhs.imag() * rhs);
}
inline Complex operator/(const Complex& lhs, double rhs) {
    return Complex(lhs.real() / rhs, lhs.imag() / rhs);
}

// Non-member operator overloads for double on left
inline Complex operator+(double lhs, const Complex& rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}
inline Complex operator-(double lhs, const Complex& rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}
inline Complex operator*(double lhs, const Complex& rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}
inline Complex operator/(double lhs, const Complex& rhs) {
    // lhs / (a + ib) = (lhs * a)/(a^2 + b^2) + (-lhs * b)/(a^2 + b^2) * i
    double denom = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    return Complex(lhs * rhs.real() / denom, -lhs * rhs.imag() / denom);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
