#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final {
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    std::uint64_t seconds() const noexcept;

    double on_earth() const noexcept;
    double on_mercury() const noexcept;
    double on_venus() const noexcept;
    double on_mars() const noexcept;
    double on_jupiter() const noexcept;
    double on_saturn() const noexcept;
    double on_uranus() const noexcept;
    double on_neptune() const noexcept;

private:
    std::uint64_t seconds_;

    static constexpr double kEarthYearSeconds = 31557600.0;
    static constexpr double kMercuryOrbitalPeriod = 0.2408467;
    static constexpr double kVenusOrbitalPeriod = 0.61519726;
    static constexpr double kEarthOrbitalPeriod = 1.0;
    static constexpr double kMarsOrbitalPeriod = 1.8808158;
    static constexpr double kJupiterOrbitalPeriod = 11.862615;
    static constexpr double kSaturnOrbitalPeriod = 29.447498;
    static constexpr double kUranusOrbitalPeriod = 84.016846;
    static constexpr double kNeptuneOrbitalPeriod = 164.79132;

    double on_planet(const double orbital_period_in_earth_years) const noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
