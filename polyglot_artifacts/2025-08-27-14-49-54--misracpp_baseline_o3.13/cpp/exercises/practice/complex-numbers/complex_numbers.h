#if !defined(COMPLEX_NUMBERS_H)
#define COMPLEX_NUMBERS_H

namespace complex_numbers {

class Complex {
 public:
  Complex(float real = 0.0f, float imag = 0.0f);

  float real() const;
  float imag() const;

  Complex operator+(const Complex& other) const;
  Complex operator-(const Complex& other) const;
  Complex operator*(const Complex& other) const;
  Complex operator/(const Complex& other) const;

  bool operator==(const Complex& other) const;
  bool operator!=(const Complex& other) const;

  Complex conj() const;
  float abs() const;
  Complex exp() const;

 private:
  float r_;
  float i_;
};

Complex operator+(double lhs, const Complex& rhs);
Complex operator-(double lhs, const Complex& rhs);
Complex operator*(double lhs, const Complex& rhs);
Complex operator/(double lhs, const Complex& rhs);

Complex operator+(const Complex& lhs, double rhs);
Complex operator-(const Complex& lhs, double rhs);
Complex operator*(const Complex& lhs, double rhs);
Complex operator/(const Complex& lhs, double rhs);

Complex conj(const Complex& value);
float   abs (const Complex& value);
Complex exp (const Complex& value);

}  // namespace complex_numbers

#endif  // COMPLEX_NUMBERS_H
