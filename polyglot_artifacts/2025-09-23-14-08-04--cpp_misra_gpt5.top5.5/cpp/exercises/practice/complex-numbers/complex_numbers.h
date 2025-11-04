#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#if defined(abs)
#undef abs
#endif
#if defined(conj)
#undef conj
#endif
#if defined(exp)
#undef exp
#endif

namespace complex_numbers {

class Complex {
public:
    // Construct with real and imaginary parts
    explicit Complex(double real = 0.0, double imag = 0.0) noexcept;

    // Accessors
    double real() const noexcept;
    double imag() const noexcept;

    // Unary operations
    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

    // Binary operations
    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

private:
    double real_;
    double imag_;
};

// Free function helpers
Complex conj(const Complex& z) noexcept;
double abs(const Complex& z) noexcept;
Complex exp(const Complex& z) noexcept;

// Mixed-type operations with doubles
Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs) noexcept;

Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;


}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
