#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
 public:
  explicit constexpr space_age(long long age_in_seconds) : seconds_(age_in_seconds) {}

  constexpr long long seconds() const { return seconds_; }
  constexpr double on_earth() const { return seconds_ / earth_year_in_seconds; }
  constexpr double on_mercury() const { return on_earth() / mercury_orbital_period; }
  constexpr double on_venus() const { return on_earth() / venus_orbital_period; }
  constexpr double on_mars() const { return on_earth() / mars_orbital_period; }
  constexpr double on_jupiter() const { return on_earth() / jupiter_orbital_period; }
  constexpr double on_saturn() const { return on_earth() / saturn_orbital_period; }
  constexpr double on_uranus() const { return on_earth() / uranus_orbital_period; }
  constexpr double on_neptune() const { return on_earth() / neptune_orbital_period; }

 private:
  long long seconds_;

  static constexpr double earth_year_in_seconds = 31557600.0;
  static constexpr double mercury_orbital_period = 0.2408467;
  static constexpr double venus_orbital_period = 0.61519726;
  static constexpr double mars_orbital_period = 1.8808158;
  static constexpr double jupiter_orbital_period = 11.862615;
  static constexpr double saturn_orbital_period = 29.447498;
  static constexpr double uranus_orbital_period = 84.016846;
  static constexpr double neptune_orbital_period = 164.79132;
};

}  // namespace space_age

#endif // SPACE_AGE_H
