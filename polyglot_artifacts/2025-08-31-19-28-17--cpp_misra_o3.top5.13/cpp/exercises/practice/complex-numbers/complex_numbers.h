#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>

namespace complex_numbers {

/*  Simple immutable complex number   */
class Complex final {
public:
    /*  Default-constructs to (0,0)  */
    constexpr Complex() noexcept : m_real(0.0), m_imag(0.0) {}

    /*  Construct from real / imag parts  */
    constexpr Complex(double r, double i) noexcept : m_real(r), m_imag(i) {}

    /*  Accessors  */
    constexpr double real() const noexcept { return m_real; }
    constexpr double imag() const noexcept { return m_imag; }

    /*  Unary operations  */
    double  abs()  const noexcept;
    Complex conj() const noexcept;
    Complex exp()  const;

    /*  Equality / inequality  */
    bool operator==(const Complex& other) const noexcept;
    bool operator!=(const Complex& other) const noexcept;

private:
    double m_real;
    double m_imag;
};

/*  Arithmetic operators  (complex–complex) */
Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, const Complex& rhs);

/*  Arithmetic operators  (complex–scalar) */
Complex operator+(const Complex& lhs, double rhs) noexcept;
Complex operator+(double lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, double rhs) noexcept;
Complex operator-(double lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, double rhs) noexcept;
Complex operator*(double lhs, const Complex& rhs) noexcept;
Complex operator/(const Complex& lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

/*  Additional operations  */
Complex  conj(const Complex& value) noexcept;
double   abs (const Complex& value) noexcept;
Complex  exp (const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
