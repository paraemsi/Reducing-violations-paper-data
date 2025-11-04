#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
public:
    Complex() noexcept = default;
    explicit Complex(double real, double imag = 0.0) noexcept;

    double real() const noexcept;
    double imag() const noexcept;

    Complex conj() const noexcept;
    double abs() const noexcept;
    Complex exp() const noexcept;

    Complex operator+(const Complex& other) const noexcept;
    Complex operator-(const Complex& other) const noexcept;
    Complex operator*(const Complex& other) const noexcept;
    Complex operator/(const Complex& other) const noexcept;

    // Operations with real numbers on the right-hand side
    Complex operator+(double rhs) const noexcept;
    Complex operator-(double rhs) const noexcept;
    Complex operator*(double rhs) const noexcept;
    Complex operator/(double rhs) const noexcept;

private:
    double m_real{0.0};
    double m_imag{0.0};
};

// Operations with real numbers on the left-hand side
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(double lhs, const Complex& rhs) noexcept;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
