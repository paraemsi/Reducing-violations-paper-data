#include "complex_numbers.h"

#include <cmath>     // std::sqrt, std::cos, std::sin, std::exp
#include <cstdint>   // fixed-width integer types (rule compliance)

namespace complex_numbers {

/* Helper alias for readability – not strictly required, but allowed */
using float64 = double;

/* Addition */
auto add(const Complex& lhs, const Complex& rhs) -> Complex
{
    return Complex{ (lhs.real() + rhs.real()), (lhs.imag() + rhs.imag()) };
}

/* Subtraction */
auto subtract(const Complex& lhs, const Complex& rhs) -> Complex
{
    return Complex{ (lhs.real() - rhs.real()), (lhs.imag() - rhs.imag()) };
}

/* Multiplication */
auto multiply(const Complex& lhs, const Complex& rhs) -> Complex
{
    return Complex{
        ( (lhs.real() * rhs.real()) - (lhs.imag() * rhs.imag()) ),
        ( (lhs.imag() * rhs.real()) + (lhs.real() * rhs.imag()) )
    };
}

/* Division */
auto divide(const Complex& lhs, const Complex& rhs) -> Complex
{
    /* Denominator: c² + d² */
    const float64 denom = ( (rhs.real() * rhs.real()) + (rhs.imag() * rhs.imag()) );

    /* Behaviour is undefined for zero denominator; caller responsibility */

    return Complex{
        ( ( (lhs.real() * rhs.real()) + (lhs.imag() * rhs.imag()) ) / denom ),
        ( ( (lhs.imag() * rhs.real()) - (lhs.real() * rhs.imag()) ) / denom )
    };
}

/* Conjugate */
auto conjugate(const Complex& z) -> Complex
{
    return Complex{ z.real(), -(z.imag()) };
}

/* Absolute value (magnitude) */
auto abs(const Complex& z) -> double
{
    return std::sqrt( (z.real() * z.real()) + (z.imag() * z.imag()) );
}

/* Exponential: e^(a + i b) = e^a (cos b + i sin b) */
auto exp(const Complex& z) -> Complex
{
    const float64 factor = std::exp(z.real());
    return Complex{
        (factor * std::cos(z.imag())),
        (factor * std::sin(z.imag()))
    };
}

/* --------------------------------------------------------------------------
 * Member operator definitions (must follow free-function declarations above)
 * --------------------------------------------------------------------------*/
auto Complex::operator+(const Complex& rhs) const -> Complex { return add(*this, rhs); }
auto Complex::operator-(const Complex& rhs) const -> Complex { return subtract(*this, rhs); }
auto Complex::operator*(const Complex& rhs) const -> Complex { return multiply(*this, rhs); }
auto Complex::operator/(const Complex& rhs) const -> Complex { return divide(*this, rhs); }

auto Complex::operator+(double rhs) const -> Complex { return Complex{ (m_real + rhs),  m_imag           }; }
auto Complex::operator-(double rhs) const -> Complex { return Complex{ (m_real - rhs),  m_imag           }; }
auto Complex::operator*(double rhs) const -> Complex { return Complex{ (m_real * rhs),  (m_imag * rhs)   }; }
auto Complex::operator/(double rhs) const -> Complex { return Complex{ (m_real / rhs),  (m_imag / rhs)   }; }

auto operator+(double lhs, const Complex& rhs) -> Complex { return Complex{ (lhs + rhs.m_real),  rhs.m_imag            }; }
auto operator-(double lhs, const Complex& rhs) -> Complex { return Complex{ (lhs - rhs.m_real), (-rhs.m_imag)          }; }
auto operator*(double lhs, const Complex& rhs) -> Complex { return Complex{ (lhs * rhs.m_real), (lhs * rhs.m_imag)     }; }
auto operator/(double lhs, const Complex& rhs) -> Complex { return divide(Complex{ lhs, 0.0 }, rhs); }

}  // namespace complex_numbers
