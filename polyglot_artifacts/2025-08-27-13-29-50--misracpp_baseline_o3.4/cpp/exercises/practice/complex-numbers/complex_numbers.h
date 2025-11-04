#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>

namespace complex_numbers {

class Complex {
private:
    double re_{0.0};
    double im_{0.0};

public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : re_{real}, im_{imag} {}

    constexpr double real() const noexcept { return re_; }
    constexpr double imag() const noexcept { return im_; }

    // Basic arithmetic
    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const;

    // Scalar overloads (Complex * double, double * Complex, Complex / double)
    Complex operator*(double scalar) const noexcept;
    Complex operator/(double scalar) const;

    // Scalar addition / subtraction
    Complex operator+(double scalar) const noexcept;
    Complex operator-(double scalar) const noexcept;

    // Unary operations
    Complex conj() const noexcept;   // complex conjugate
    double  abs()  const noexcept;   // magnitude
    Complex exp()  const;            // e^(a + ib)

    // Equality helpers (with tolerance)
    bool operator==(const Complex& other) const noexcept;
    bool operator!=(const Complex& other) const noexcept { return !(*this == other); }
};

// Non-member overloads for commutativity with scalars
Complex operator*(double scalar, const Complex& z) noexcept;
Complex operator+(double scalar, const Complex& z) noexcept;
Complex operator-(double scalar, const Complex& z) noexcept;
Complex operator/(double scalar, const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
