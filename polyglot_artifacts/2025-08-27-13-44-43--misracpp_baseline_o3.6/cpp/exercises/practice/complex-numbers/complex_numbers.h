#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

#include <cmath>
#include <iosfwd>

namespace complex_numbers {

class Complex {
public:
    Complex() = default;
    Complex(double real, double imag);

    double real() const;
    double imag() const;

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);
    Complex& operator*=(double scalar);
    Complex& operator/=(double scalar);

    Complex operator-() const;

    Complex conj() const;
    double abs() const;
    Complex exp() const;

private:
    double real_{0.0};
    double imag_{0.0};
};

Complex exp(const Complex& z);

Complex operator+(Complex lhs, const Complex& rhs);
Complex operator-(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, const Complex& rhs);
Complex operator/(Complex lhs, const Complex& rhs);
Complex operator*(Complex lhs, double rhs);
Complex operator*(double lhs, Complex rhs);
Complex operator/(Complex lhs, double rhs);
Complex operator+(Complex lhs, double rhs);
Complex operator+(double lhs, Complex rhs);
Complex operator-(Complex lhs, double rhs);
Complex operator-(double lhs, Complex rhs);
Complex operator/(double lhs, Complex rhs);

Complex conj(const Complex& z);
double abs(const Complex& z);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& os, const Complex& z);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
