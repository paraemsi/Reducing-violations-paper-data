#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <iosfwd>
#include <ostream>  // ensure complete declaration for std::ostream users

namespace complex_numbers {

class Complex {
public:
    Complex() = default;
    Complex(double r, double i);

    double real() const;
    double imag() const;

    // Unary operators
    Complex operator+() const;        // +z
    Complex operator-() const;        // -z

    // Member utility operations
    Complex conj() const;             // complex conjugate
    double  abs()  const;             // magnitude
    Complex exp()  const;             // e^z

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

private:
    double real_{0.0};
    double imag_{0.0};
};

// Non-member arithmetic operators
Complex operator+(Complex lhs, const Complex& rhs);
Complex operator-(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, const Complex& rhs);
Complex operator/(Complex lhs, const Complex& rhs);

// Real-scalar multiplication helpers
Complex operator*(double lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, double rhs);

// Complex-scalar helpers
Complex operator+(Complex lhs, double rhs);
Complex operator+(double lhs, const Complex& rhs);

Complex operator-(Complex lhs, double rhs);
Complex operator-(double lhs, const Complex& rhs);

Complex operator/(Complex lhs, double rhs);
Complex operator/(double lhs, const Complex& rhs);

// Comparison operators
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

// Other operations
Complex conj(const Complex& c);
double  abs(const Complex& c);
Complex exp(const Complex& c);

// Optional stream output
std::ostream& operator<<(std::ostream& os, const Complex& c);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
