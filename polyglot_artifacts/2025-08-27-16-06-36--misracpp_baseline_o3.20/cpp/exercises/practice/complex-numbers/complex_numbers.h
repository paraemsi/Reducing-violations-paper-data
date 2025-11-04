#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

/**
 * A very small Complex number class implementing the minimum functionality
 * required by the exercise.  It purposefully keeps the interface minimal
 * while adhering to the rules given.
 */
class Complex {
public:
    constexpr Complex(double real = 0.0, double imag = 0.0) noexcept
        : real_{real}, imag_{imag} {}

    // Accessors
    constexpr double real() const noexcept { return real_; }
    constexpr double imag() const noexcept { return imag_; }

    // Additional operations as member functions
    double   abs()  const noexcept;
    Complex  conj() const noexcept;
    Complex  exp()  const noexcept;
    Complex  operator-() const noexcept;

    // Compound-assignment operators
    Complex& operator+=(const Complex& other) noexcept;
    Complex& operator-=(const Complex& other) noexcept;
    Complex& operator*=(const Complex& other) noexcept;
    Complex& operator/=(const Complex& other);

private:
    double real_;
    double imag_;
};

/* Arithmetic operators implemented in terms of the compound versions. */
Complex operator+(Complex lhs, const Complex& rhs) noexcept;
Complex operator-(Complex lhs, const Complex& rhs) noexcept;
Complex operator*(Complex lhs, const Complex& rhs) noexcept;
Complex operator/(Complex lhs, const Complex& rhs);

/* Exact comparison operators */
bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

/* Additional required operations */
Complex  conjugate(const Complex& z) noexcept;
double   abs(const Complex& z) noexcept;
Complex  exp(const Complex& z) noexcept;
Complex  conj(const Complex& z) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
