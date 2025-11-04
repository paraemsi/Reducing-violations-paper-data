#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;

public:
    Complex(double r = 0.0, double i = 0.0) : real_(r), imag_(i) {}

    double real() const {
        return real_;
    }

    double imag() const {
        return imag_;
    }

    Complex operator+(const Complex& other) const {
        return Complex((real_ + other.real_), (imag_ + other.imag_));
    }

    Complex operator-(const Complex& other) const {
        return Complex((real_ - other.real_), (imag_ - other.imag_));
    }

    Complex operator*(const Complex& other) const {
        return Complex(((real_ * other.real_) - (imag_ * other.imag_)), ((imag_ * other.real_) + (real_ * other.imag_)));
    }

    Complex operator/(const Complex& other) const {
        double denom = ((other.real_ * other.real_) + (other.imag_ * other.imag_));
        double new_real = (((real_ * other.real_) + (imag_ * other.imag_)) / denom);
        double new_imag = (((imag_ * other.real_) - (real_ * other.imag_)) / denom);
        return Complex(new_real, new_imag);
    }

    Complex conj() const {
        return Complex(real_, (-imag_));
    }

    double abs() const {
        return std::sqrt(((real_ * real_) + (imag_ * imag_)));
    }

    Complex exp() const {
        double e_real = std::exp(real_);
        double cos_imag = std::cos(imag_);
        double sin_imag = std::sin(imag_);
        return Complex((e_real * cos_imag), (e_real * sin_imag));
    }
};

Complex operator+(double lhs, const Complex& rhs) {
    return Complex((lhs + rhs.real()), rhs.imag());
}

Complex operator-(double lhs, const Complex& rhs) {
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

Complex operator*(double lhs, const Complex& rhs) {
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

Complex operator/(double lhs, const Complex& rhs) {
    double denom = ((rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()));
    return Complex(((lhs * rhs.real()) / denom), ((-lhs * rhs.imag()) / denom));
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
