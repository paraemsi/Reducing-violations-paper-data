#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final {
public:
    using seconds_type = std::uint64_t;

    explicit space_age(seconds_type seconds) noexcept;

    seconds_type seconds() const noexcept;

    double on_earth() const noexcept;
    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    static constexpr double seconds_per_earth_year = 31557600.0;
    static constexpr double mercury_orbital_years = 0.2408467;
    static constexpr double venus_orbital_years = 0.61519726;
    static constexpr double earth_orbital_years = 1.0;
    static constexpr double mars_orbital_years = 1.8808158;
    static constexpr double jupiter_orbital_years = 11.862615;
    static constexpr double saturn_orbital_years = 29.447498;
    static constexpr double uranus_orbital_years = 84.016846;
    static constexpr double neptune_orbital_years = 164.79132;

    double on_planet(double orbital_period_in_earth_years) const noexcept;

    seconds_type seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
