#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept;
    Complex(double real, double imag) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    // Operations with another complex number
    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

    // Operations with a real number
    Complex operator+(double rhs) const noexcept;
    Complex operator-(double rhs) const noexcept;
    Complex operator*(double rhs) const noexcept;
    Complex operator/(double rhs) const noexcept;

    // Other operations
    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const;

private:
    double r_;
    double i_;
};

// Real on the left-hand side overloads
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

// Free function operations for compatibility
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z);
double real(const Complex& z) noexcept;
double imag(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
