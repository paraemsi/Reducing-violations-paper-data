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
    Complex operator+(double rhs) const {
        return Complex(real_ + rhs, imag_);
    }
    friend Complex operator+(double lhs, const Complex& rhs) {
        return Complex(lhs + rhs.real_, rhs.imag_);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }
    Complex operator-(double rhs) const {
        return Complex(real_ - rhs, imag_);
    }
    friend Complex operator-(double lhs, const Complex& rhs) {
        return Complex(lhs - rhs.real_, -rhs.imag_);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real_ * other.real_ - imag_ * other.imag_,
            real_ * other.imag_ + imag_ * other.real_
        );
    }
    Complex operator*(double rhs) const {
        return Complex(real_ * rhs, imag_ * rhs);
    }
    friend Complex operator*(double lhs, const Complex& rhs) {
        return Complex(lhs * rhs.real_, lhs * rhs.imag_);
    }

    Complex operator/(const Complex& other) const {
        double denom = other.real_ * other.real_ + other.imag_ * other.imag_;
        return Complex(
            (real_ * other.real_ + imag_ * other.imag_) / denom,
            (imag_ * other.real_ - real_ * other.imag_) / denom
        );
    }
    Complex operator/(double rhs) const {
        return Complex(real_ / rhs, imag_ / rhs);
    }
    friend Complex operator/(double lhs, const Complex& rhs) {
        double denom = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
        return Complex(
            (lhs * rhs.real_) / denom,
            (-lhs * rhs.imag_) / denom
        );
    }

    Complex conj() const {
        return Complex(real_, -imag_);
    }

    double abs() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }

    Complex exp() const {
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

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
