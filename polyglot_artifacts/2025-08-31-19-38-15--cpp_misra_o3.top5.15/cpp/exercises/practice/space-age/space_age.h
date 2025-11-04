#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(std::uint64_t seconds_in);

    std::uint64_t seconds() const;

    double on_earth() const;
    double on_mercury() const;
    double on_venus() const;
    double on_mars() const;
    double on_jupiter() const;
    double on_saturn() const;
    double on_uranus() const;
    double on_neptune() const;

private:
    std::uint64_t seconds_;

    static constexpr double earth_year_in_seconds = 31557600.0;

    static constexpr double mercury_orbital = 0.2408467;
    static constexpr double venus_orbital   = 0.61519726;
    static constexpr double mars_orbital    = 1.8808158;
    static constexpr double jupiter_orbital = 11.862615;
    static constexpr double saturn_orbital  = 29.447498;
    static constexpr double uranus_orbital  = 84.016846;
    static constexpr double neptune_orbital = 164.79132;

    double age_on_planet(double orbital_period) const;
};

}  // namespace space_age

#endif // SPACE_AGE_H
