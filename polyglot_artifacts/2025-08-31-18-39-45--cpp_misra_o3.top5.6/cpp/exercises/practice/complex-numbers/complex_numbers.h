#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex
{
public:
    /* Constructor */
    constexpr Complex(double real_value = 0.0, double imag_value = 0.0) noexcept;

    /* Accessors */
    constexpr double real() const noexcept;
    constexpr double imag() const noexcept;

    /* Arithmetic operators */
    constexpr Complex operator+(const Complex& other) const noexcept;
    constexpr Complex operator-(const Complex& other) const noexcept;
    constexpr Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const;

    /* Other operations */
    constexpr Complex conj() const noexcept;
    double abs() const;
    Complex exp() const;

private:
    double m_real;
    double m_imag;
};

/* Free-standing arithmetic with a scalar on the left-hand side */
constexpr Complex operator+(double lhs, const Complex& rhs) noexcept;
constexpr Complex operator-(double lhs, const Complex& rhs) noexcept;
constexpr Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
