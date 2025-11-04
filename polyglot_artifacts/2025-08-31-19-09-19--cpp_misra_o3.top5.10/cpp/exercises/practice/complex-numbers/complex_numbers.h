#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>     // std::sqrt, std::cos, std::sin, std::exp

namespace complex_numbers {

struct Complex
{
private:
    double m_real;
    double m_imag;

public:
    /* Constructor with default arguments */
    explicit Complex(double r = 0.0, double i = 0.0) : m_real(r), m_imag(i) {}

    /* Accessors */
    auto real() const -> double { return m_real; }
    auto imag() const -> double { return m_imag; }

    /* Unary-like member operations */
    auto conj() const -> Complex { return Complex{ m_real, -m_imag }; }
    auto abs()  const -> double  { return std::sqrt( (m_real * m_real) + (m_imag * m_imag) ); }
    auto exp()  const -> Complex
    {
        const double factor = std::exp(m_real);
        return Complex{ (factor * std::cos(m_imag)), (factor * std::sin(m_imag)) };
    }

    /* Binary arithmetic with Complex rhs */
    auto operator+(const Complex& rhs) const -> Complex;
    auto operator-(const Complex& rhs) const -> Complex;
    auto operator*(const Complex& rhs) const -> Complex;
    auto operator/(const Complex& rhs) const -> Complex;

    /* Binary arithmetic with scalar rhs */
    auto operator+(double rhs) const -> Complex;
    auto operator-(double rhs) const -> Complex;
    auto operator*(double rhs) const -> Complex;
    auto operator/(double rhs) const -> Complex;

    /* Symmetric scalar–Complex operators */
    friend auto operator+(double lhs, const Complex& rhs) -> Complex;
    friend auto operator-(double lhs, const Complex& rhs) -> Complex;
    friend auto operator*(double lhs, const Complex& rhs) -> Complex;
    friend auto operator/(double lhs, const Complex& rhs) -> Complex;
};

/* Arithmetic operations */
auto add(const Complex& lhs, const Complex& rhs) -> Complex;
auto subtract(const Complex& lhs, const Complex& rhs) -> Complex;
auto multiply(const Complex& lhs, const Complex& rhs) -> Complex;
auto divide(const Complex& lhs, const Complex& rhs) -> Complex;

/* Unary-like operations */
auto conjugate(const Complex& z) -> Complex;
auto abs(const Complex& z) -> double;
auto exp(const Complex& z) -> Complex;

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
