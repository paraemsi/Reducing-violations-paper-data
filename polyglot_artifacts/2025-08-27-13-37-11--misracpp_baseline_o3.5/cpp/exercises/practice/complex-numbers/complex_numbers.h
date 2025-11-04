#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    // Constructors
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : real_{real}, imag_{imag} {}

    // Accessors
    constexpr double real() const noexcept { return real_; }
    constexpr double imag() const noexcept { return imag_; }

    // Basic arithmetic operations
    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const;
    Complex operator*(double other) const noexcept;
    Complex operator/(double other) const;
    Complex operator+(double other) const noexcept;
    Complex operator-(double other) const noexcept;

    // Compound assignment operators
    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator/=(const Complex& other);

    // Comparison operators
    bool operator==(const Complex& other) const noexcept;
    bool operator!=(const Complex& other) const noexcept;

    // Derived operations
    Complex conj() const noexcept;
    double  abs() const noexcept;
    Complex exp() const;

private:
    double real_;
    double imag_;
};
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
