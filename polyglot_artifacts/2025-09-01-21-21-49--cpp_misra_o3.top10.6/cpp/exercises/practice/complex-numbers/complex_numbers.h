#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <cstdint>
#include <limits>

namespace complex_numbers {

/* Forward declaration */
class Complex;

/* Symmetrical binary operators – declared before the class for friend-ship */
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs) noexcept;

/* Overloads with real scalar on either side */
[[nodiscard]] Complex operator+(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator+(double lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator-(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator-(double lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator*(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator*(double lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator/(const Complex& lhs, double rhs) noexcept;
[[nodiscard]] Complex operator/(double lhs, const Complex& rhs) noexcept;

/* Helper free-functions for unary operations */
[[nodiscard]] Complex conjugate(const Complex& z) noexcept;
[[nodiscard]] double  abs(const Complex& z) noexcept;
[[nodiscard]] Complex exp(const Complex& z) noexcept;

class Complex final {
public:
    constexpr Complex() noexcept : real_{0.0}, imag_{0.0} {}
    constexpr Complex(double realValue, double imagValue) noexcept : real_{realValue}, imag_{imagValue} {}

    [[nodiscard]] constexpr double real() const noexcept { return real_; }
    [[nodiscard]] constexpr double imag() const noexcept { return imag_; }

        /* Alias expected by tests */
        [[nodiscard]] constexpr Complex conj() const noexcept
        {
            return conjugate();
        }

    [[nodiscard]] constexpr Complex conjugate() const noexcept
    {
        return Complex(real_, (-imag_));
    }

    [[nodiscard]] double abs() const noexcept
    {
        /* |z| = sqrt(a^2 + b^2) */
        return std::sqrt((real_ * real_) + (imag_ * imag_));
    }

    [[nodiscard]] Complex exp() const noexcept
    {
        /* e^(a + i b) = e^a * (cos(b) + i sin(b)) */
        const double magnitude{std::exp(real_)};
        const double cosPart{std::cos(imag_)};
        const double sinPart{std::sin(imag_)};
        return Complex((magnitude * cosPart), (magnitude * sinPart));
    }

    /* Grant non-member operators access to private members */
    friend Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
    friend Complex operator/(const Complex& lhs, const Complex& rhs) noexcept;

private:
    double real_;
    double imag_;
};

/* ---------- operator definitions ---------- */
[[nodiscard]] inline Complex operator+(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real_ + rhs.real_), (lhs.imag_ + rhs.imag_));
}

[[nodiscard]] inline Complex operator-(const Complex& lhs, const Complex& rhs) noexcept
{
    return Complex((lhs.real_ - rhs.real_), (lhs.imag_ - rhs.imag_));
}

[[nodiscard]] inline Complex operator*(const Complex& lhs, const Complex& rhs) noexcept
{
    /* (a + i b)(c + i d) = (ac - bd) + (bc + ad)i */
    const double realPart{(lhs.real_ * rhs.real_) - (lhs.imag_ * rhs.imag_)};
    const double imagPart{(lhs.imag_ * rhs.real_) + (lhs.real_ * rhs.imag_)};
    return Complex(realPart, imagPart);
}

/* ---------- unary helper definitions ---------- */
[[nodiscard]] inline Complex conjugate(const Complex& z) noexcept
{
    return z.conjugate();
}

[[nodiscard]] inline double abs(const Complex& z) noexcept
{
    return z.abs();
}

[[nodiscard]] inline Complex exp(const Complex& z) noexcept
{
    return z.exp();
}

[[nodiscard]] inline Complex operator/(const Complex& lhs, const Complex& rhs) noexcept
{
    /* (a + i b)/(c + i d) = [(ac + bd) + (bc - ad)i] / (c^2 + d^2) */
    const double denom{(rhs.real_ * rhs.real_) + (rhs.imag_ * rhs.imag_)};

    if (denom == 0.0) {
        /* Return NaN components on division by zero */
        return Complex(std::numeric_limits<double>::quiet_NaN(),
                       std::numeric_limits<double>::quiet_NaN());
    }

    const double realPart{((lhs.real_ * rhs.real_) + (lhs.imag_ * rhs.imag_)) / denom};
    const double imagPart{((lhs.imag_ * rhs.real_) - (lhs.real_ * rhs.imag_)) / denom};
    return Complex(realPart, imagPart);
}

/* ---------- scalar/complex operator overloads ---------- */
[[nodiscard]] inline Complex operator+(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() + rhs), lhs.imag());
}

[[nodiscard]] inline Complex operator+(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs + rhs.real()), rhs.imag());
}

[[nodiscard]] inline Complex operator-(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() - rhs), lhs.imag());
}

[[nodiscard]] inline Complex operator-(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs - rhs.real()), (-rhs.imag()));
}

[[nodiscard]] inline Complex operator*(const Complex& lhs, double rhs) noexcept
{
    return Complex((lhs.real() * rhs), (lhs.imag() * rhs));
}

[[nodiscard]] inline Complex operator*(double lhs, const Complex& rhs) noexcept
{
    return Complex((lhs * rhs.real()), (lhs * rhs.imag()));
}

[[nodiscard]] inline Complex operator/(const Complex& lhs, double rhs) noexcept
{
    if (rhs == 0.0) {
        return Complex(std::numeric_limits<double>::quiet_NaN(),
                       std::numeric_limits<double>::quiet_NaN());
    }
    return Complex((lhs.real() / rhs), (lhs.imag() / rhs));
}

[[nodiscard]] inline Complex operator/(double lhs, const Complex& rhs) noexcept
{
    return Complex(lhs, 0.0) / rhs;
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
