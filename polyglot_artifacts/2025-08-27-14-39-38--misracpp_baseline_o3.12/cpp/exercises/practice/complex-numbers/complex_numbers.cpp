#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

bool Complex::operator==(const Complex& other) const {
    return std::abs(m_real - other.m_real) < kEpsilon &&
           std::abs(m_imag - other.m_imag) < kEpsilon;
}

double Complex::abs() const {
    return std::sqrt(m_real * m_real + m_imag * m_imag);
}

Complex Complex::operator/(const Complex& other) const {
    double denom = other.m_real * other.m_real + other.m_imag * other.m_imag;
    return {(m_real * other.m_real + m_imag * other.m_imag) / denom,
            (m_imag * other.m_real - m_real * other.m_imag) / denom};
}

Complex Complex::exp() const {
    double exp_real = std::exp(m_real);
    return {exp_real * std::cos(m_imag), exp_real * std::sin(m_imag)};
}


}  // namespace complex_numbers
