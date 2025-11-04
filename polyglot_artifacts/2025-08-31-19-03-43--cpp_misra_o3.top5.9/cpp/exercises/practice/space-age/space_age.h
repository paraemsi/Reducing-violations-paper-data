#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age
{
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    [[nodiscard]] std::uint64_t seconds() const noexcept;

    [[nodiscard]] double on_earth() const noexcept;
    [[nodiscard]] double on_mercury() const noexcept;
    [[nodiscard]] double on_venus() const noexcept;
    [[nodiscard]] double on_mars() const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn() const noexcept;
    [[nodiscard]] double on_uranus() const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    std::uint64_t m_seconds;

    static constexpr double EARTH_YEAR_SECONDS { 31'557'600.0 };

    static constexpr double ORBIT_RATIO_MERCURY { 0.2408467 };
    static constexpr double ORBIT_RATIO_VENUS   { 0.61519726 };
    static constexpr double ORBIT_RATIO_EARTH   { 1.0 };
    static constexpr double ORBIT_RATIO_MARS    { 1.8808158 };
    static constexpr double ORBIT_RATIO_JUPITER { 11.862615 };
    static constexpr double ORBIT_RATIO_SATURN  { 29.447498 };
    static constexpr double ORBIT_RATIO_URANUS  { 84.016846 };
    static constexpr double ORBIT_RATIO_NEPTUNE { 164.79132 };

    [[nodiscard]] double on_planet(double orbital_ratio) const noexcept;
};

}  // namespace space_age

#endif // SPACE_AGE_H
