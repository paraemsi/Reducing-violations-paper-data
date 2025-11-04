#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
 public:
  explicit space_age(long long seconds);

  long long seconds() const;

  double on_mercury() const;
  double on_venus() const;
  double on_earth() const;
  double on_mars() const;
  double on_jupiter() const;
  double on_saturn() const;
  double on_uranus() const;
  double on_neptune() const;

 private:
  static constexpr double kSecondsPerEarthYear = 31'557'600.0;
  static constexpr double kEarthYearRatioMercury = 0.2408467;
  static constexpr double kEarthYearRatioVenus   = 0.61519726;
  static constexpr double kEarthYearRatioEarth   = 1.0;
  static constexpr double kEarthYearRatioMars    = 1.8808158;
  static constexpr double kEarthYearRatioJupiter = 11.862615;
  static constexpr double kEarthYearRatioSaturn  = 29.447498;
  static constexpr double kEarthYearRatioUranus  = 84.016846;
  static constexpr double kEarthYearRatioNeptune = 164.79132;

  long long seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
