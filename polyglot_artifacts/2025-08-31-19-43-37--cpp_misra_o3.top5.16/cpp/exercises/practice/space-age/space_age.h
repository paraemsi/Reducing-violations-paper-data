#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
public:
    explicit space_age(std::int64_t seconds) noexcept;
    std::int64_t seconds() const noexcept;

    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_earth() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    static constexpr double earth_year_in_seconds = 31557600.0;
    static constexpr double mercury_orbital_period = 0.2408467;
    static constexpr double venus_orbital_period = 0.61519726;
    static constexpr double mars_orbital_period = 1.8808158;
    static constexpr double jupiter_orbital_period = 11.862615;
    static constexpr double saturn_orbital_period = 29.447498;
    static constexpr double uranus_orbital_period = 84.016846;
    static constexpr double neptune_orbital_period = 164.79132;

    double age_on_planet(double orbital_period) const noexcept;

    std::int64_t seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
