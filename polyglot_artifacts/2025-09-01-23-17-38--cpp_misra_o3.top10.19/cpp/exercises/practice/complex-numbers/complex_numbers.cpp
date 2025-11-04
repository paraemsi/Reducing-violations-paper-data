#include "complex_numbers.h"
#include <cmath>

namespace complex_numbers {

Complex::Complex(double realPart, double imagPart) noexcept
    : m_real(realPart), m_imag(imagPart) {}

double Complex::real() const noexcept {
    return m_real;
}

double Complex::imag() const noexcept {
    return m_imag;
}

Complex& Complex::operator+=(const Complex& rhs) noexcept {
    m_real += rhs.m_real;
    m_imag += rhs.m_imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs) noexcept {
    m_real -= rhs.m_real;
    m_imag -= rhs.m_imag;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) noexcept {
    const double newReal = (m_real * rhs.m_real) - (m_imag * rhs.m_imag);
    const double newImag = (m_imag * rhs.m_real) + (m_real * rhs.m_imag);
    m_real = newReal;
    m_imag = newImag;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    const double denom = (rhs.m_real * rhs.m_real) + (rhs.m_imag * rhs.m_imag);
    const double newReal = ((m_real * rhs.m_real) + (m_imag * rhs.m_imag)) / denom;
    const double newImag = ((m_imag * rhs.m_real) - (m_real * rhs.m_imag)) / denom;
    m_real = newReal;
    m_imag = newImag;
    return *this;
}

Complex Complex::conjugate() const noexcept {
    return Complex(m_real, -m_imag);
}

double Complex::abs() const noexcept {
    return std::sqrt((m_real * m_real) + (m_imag * m_imag));
}

Complex Complex::conj() const noexcept {
    return conjugate();
}

Complex Complex::exp() const {
    return complex_numbers::exp(*this);
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    Complex result(lhs);
    result += rhs;
    return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    Complex result(lhs);
    result -= rhs;
    return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    Complex result(lhs);
    result *= rhs;
    return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    Complex result(lhs);
    result /= rhs;
    return result;
}

Complex exp(const Complex& value) {
    const double expReal = std::exp(value.real());
    const double cosImag = std::cos(value.imag());
    const double sinImag = std::sin(value.imag());
    return Complex((expReal * cosImag), (expReal * sinImag));
}

}  // namespace complex_numbers
