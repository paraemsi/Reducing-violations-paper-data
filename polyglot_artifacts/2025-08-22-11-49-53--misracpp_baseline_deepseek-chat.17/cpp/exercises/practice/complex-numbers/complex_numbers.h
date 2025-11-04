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
        double exp_real = std::exp(real_) * std::cos(imag_);
        double exp_imag = std::exp(real_) * std::sin(imag_);
        return Complex(exp_real, exp_imag);
    }
    
    Complex operator+(const Complex& other) const {
        return Complex(real_ + other.real_, imag_ + other.imag_);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real_ - other.real_, imag_ - other.imag_);
    }
    
    Complex operator*(const Complex& other) const {
        double result_real = real_ * other.real_ - imag_ * other.imag_;
        double result_imag = imag_ * other.real_ + real_ * other.imag_;
        return Complex(result_real, result_imag);
    }
    
    Complex operator/(const Complex& other) const {
        double denominator = other.real_ * other.real_ + other.imag_ * other.imag_;
        double result_real = (real_ * other.real_ + imag_ * other.imag_) / denominator;
        double result_imag = (imag_ * other.real_ - real_ * other.imag_) / denominator;
        return Complex(result_real, result_imag);
    }
    
    // Add operators for Complex + double, etc.
    Complex operator+(double other) const {
        return Complex(real_ + other, imag_);
    }
    
    Complex operator-(double other) const {
        return Complex(real_ - other, imag_);
    }
    
    Complex operator*(double other) const {
        return Complex(real_ * other, imag_ * other);
    }
    
    Complex operator/(double other) const {
        return Complex(real_ / other, imag_ / other);
    }
};

// Add non-member operators for double + Complex, etc.
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
    double denominator = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    double result_real = (lhs * rhs.real()) / denominator;
    double result_imag = (-lhs * rhs.imag()) / denominator;
    return Complex(result_real, result_imag);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
