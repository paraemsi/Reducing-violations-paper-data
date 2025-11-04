#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
private:
    long long seconds_;
    static constexpr double earth_seconds_per_year = 31557600.0;
    static constexpr double mercury_orbital_period = 0.2408467;
    static constexpr double venus_orbital_period = 0.61519726;
    static constexpr double earth_orbital_period = 1.0;
    static constexpr double mars_orbital_period = 1.8808158;
    static constexpr double jupiter_orbital_period = 11.862615;
    static constexpr double saturn_orbital_period = 29.447498;
    static constexpr double uranus_orbital_period = 84.016846;
    static constexpr double neptune_orbital_period = 164.79132;

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
};

}  // namespace space_age

#endif // SPACE_AGE_H
