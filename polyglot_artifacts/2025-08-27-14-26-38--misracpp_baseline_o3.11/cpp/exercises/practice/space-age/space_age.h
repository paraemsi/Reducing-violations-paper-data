#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

namespace space_age {

class space_age {
public:
    explicit space_age(unsigned long long seconds);

    unsigned long long seconds() const;

    double on_mercury() const;
    double on_venus() const;
    double on_earth() const;
    double on_mars() const;
    double on_jupiter() const;
    double on_saturn() const;
    double on_uranus() const;
    double on_neptune() const;

private:
    unsigned long long seconds_;

    static constexpr double earth_year_seconds = 31'557'600.0; // 365.25 days

    // Orbital period factors relative to an Earth year
    static constexpr double mercury_factor = 0.2408467;
    static constexpr double venus_factor   = 0.61519726;
    static constexpr double mars_factor    = 1.8808158;
    static constexpr double jupiter_factor = 11.862615;
    static constexpr double saturn_factor  = 29.447498;
    static constexpr double uranus_factor  = 84.016846;
    static constexpr double neptune_factor = 164.79132;

    double age_on_planet(double orbital_period_factor) const;
};

}  // namespace space_age

#endif // SPACE_AGE_H
