#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cstdint>   // fixed-width integer types (MISRA C++)
#include <cmath>     // std::sqrt – required by abs()

// Forward declare symbols used further below
namespace complex_numbers {

struct Complex; // forward declaration of the aggregate

Complex add(Complex const& lhs, Complex const& rhs) noexcept;
Complex subtract(Complex const& lhs, Complex const& rhs) noexcept;
Complex multiply(Complex const& lhs, Complex const& rhs) noexcept;
Complex divide(Complex const& lhs, Complex const& rhs);

Complex  conjugate(Complex const& value) noexcept;
double   abs      (Complex const& value) noexcept;
Complex  exp      (Complex const& value) noexcept;

// A lightweight aggregate to hold the real and imaginary parts
struct Complex final
{
    /* data members renamed to avoid collision with accessor
       member functions expected by the tests */
    double real_{};
    double imag_{};

    // Constructors
    constexpr Complex() noexcept = default;
    constexpr Complex(double r, double i) noexcept : real_{r}, imag_{i} {}

    // Observers
    double real() const noexcept { return real_; }
    double imag() const noexcept { return imag_; }

    /* legacy helpers kept for internal use */
    double real_part() const noexcept { return real_; }
    double imag_part() const noexcept { return imag_; }

    // Unary operations
    Complex conj() const noexcept { return conjugate(*this); }
    double  abs()  const noexcept { return complex_numbers::abs(*this); }
    Complex exp()  const noexcept { return complex_numbers::exp(*this); }

    // Compound assignment
    Complex& operator+=(Complex const& other) noexcept
    {
        *this = add(*this, other);
        return *this;
    }

    Complex& operator-=(Complex const& other) noexcept
    {
        *this = subtract(*this, other);
        return *this;
    }

    Complex& operator*=(Complex const& other) noexcept
    {
        *this = multiply(*this, other);
        return *this;
    }

    Complex& operator/=(Complex const& other)
    {
        *this = divide(*this, other);
        return *this;
    }
};

// Factory helper – keeps construction uniform
constexpr Complex make_complex(double real, double imag) noexcept
{
    return Complex{real, imag};
}


// (duplicate declarations removed – prototypes are already provided above)

// Inline arithmetic operators
inline Complex operator+(Complex lhs, Complex const& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}

inline Complex operator-(Complex lhs, Complex const& rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}

inline Complex operator*(Complex lhs, Complex const& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}

inline Complex operator/(Complex lhs, Complex const& rhs)
{
    lhs /= rhs;
    return lhs;
}

/* === scalar (double) interactions === */
inline Complex operator+(Complex lhs, double rhs) noexcept
{
    return Complex{(lhs.real_ + rhs), lhs.imag_};
}

inline Complex operator+(double lhs, Complex rhs) noexcept
{
    return (rhs + lhs);
}

inline Complex operator-(Complex lhs, double rhs) noexcept
{
    return Complex{(lhs.real_ - rhs), lhs.imag_};
}

inline Complex operator-(double lhs, Complex rhs) noexcept
{
    return Complex{(lhs - rhs.real_), (-rhs.imag_)};
}

inline Complex operator*(Complex lhs, double rhs) noexcept
{
    return Complex{(lhs.real_ * rhs), (lhs.imag_ * rhs)};
}

inline Complex operator*(double lhs, Complex rhs) noexcept
{
    return (rhs * lhs);
}

inline Complex operator/(Complex lhs, double rhs)
{
    return Complex{(lhs.real_ / rhs), (lhs.imag_ / rhs)};
}

inline Complex operator/(double lhs, Complex const& rhs)
{
    return divide(Complex{lhs, 0.0}, rhs);
}

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
