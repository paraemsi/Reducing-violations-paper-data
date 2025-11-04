#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double real_;
    double imag_;
public:
    Complex(double real, double imag) : real_(real), imag_(imag) {}
    double real() const { return real_; }
    double imag() const { return imag_; }
    double abs() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }
    Complex conj() const {
        return Complex(real_, -imag_);
    }
    Complex exp() const {
        // e^(a + bi) = e^a * (cos(b) + i*sin(b))
        double magnitude = std::exp(real_);
        return Complex(magnitude * std::cos(imag_), magnitude * std::sin(imag_));
    }
    
    // Overload operators
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }
    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }
    Complex operator*(const Complex& other) const {
        // (a + bi)*(c + di) = (ac - bd) + (ad + bc)i
        double real_part = real_ * other.real_ - imag_ * other.imag_;
        double imag_part = imag_ * other.real_ + real_ * other.imag_;
        return Complex(real_part, imag_part);
    }
    Complex operator/(const Complex& other) const {
        // (a + bi)/(c + di) = [(ac + bd)/(c^2 + d^2)] + [(bc - ad)/(c^2 + d^2)]i
        double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
        double real_part = (real_ * other.real_ + imag_ * other.imag_) / denominator;
        double imag_part = (imag_ * other.real_ - real_ * other.imag_) / denominator;
        return Complex(real_part, imag_part);
    }
    
    // Friend operators for operations with doubles
    friend Complex operator+(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ + rhs, lhs.imag_);
    }
    friend Complex operator+(double lhs, const Complex& rhs) {
        return Complex(lhs + rhs.real_, rhs.imag_);
    }
    friend Complex operator-(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ - rhs, lhs.imag_);
    }
    friend Complex operator-(double lhs, const Complex& rhs) {
        return Complex(lhs - rhs.real_, -rhs.imag_);
    }
    friend Complex operator*(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ * rhs, lhs.imag_ * rhs);
    }
    friend Complex operator*(double lhs, const Complex& rhs) {
        return Complex(lhs * rhs.real_, lhs * rhs.imag_);
    }
    friend Complex operator/(const Complex& lhs, double rhs) {
        return Complex(lhs.real_ / rhs, lhs.imag_ / rhs);
    }
    friend Complex operator/(double lhs, const Complex& rhs) {
        // To compute lhs / (a + bi), we can use the formula for division
        // which is the same as multiplying lhs by the reciprocal of rhs
        double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
        return Complex((lhs * rhs.real_) / denominator, (-lhs * rhs.imag_) / denominator);
    }
};

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
