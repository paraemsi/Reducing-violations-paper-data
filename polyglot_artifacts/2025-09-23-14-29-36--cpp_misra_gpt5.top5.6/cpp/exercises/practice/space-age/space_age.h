#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age {
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

    static constexpr double earth_year_seconds() noexcept { return 31557600.0; }
    static constexpr double orbital_period_mercury() noexcept { return 0.2408467; }
    static constexpr double orbital_period_venus() noexcept { return 0.61519726; }
    static constexpr double orbital_period_earth() noexcept { return 1.0; }
    static constexpr double orbital_period_mars() noexcept { return 1.8808158; }
    static constexpr double orbital_period_jupiter() noexcept { return 11.862615; }
    static constexpr double orbital_period_saturn() noexcept { return 29.447498; }
    static constexpr double orbital_period_uranus() noexcept { return 84.016846; }
    static constexpr double orbital_period_neptune() noexcept { return 164.79132; }

    double age_on(double orbital_period) const noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
