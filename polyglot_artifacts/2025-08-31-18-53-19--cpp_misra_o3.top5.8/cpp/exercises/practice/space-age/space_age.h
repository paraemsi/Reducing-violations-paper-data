#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final
{
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    auto seconds() const noexcept -> std::uint64_t;

    auto on_earth()   const noexcept -> double;
    auto on_mercury() const noexcept -> double;
    auto on_venus()   const noexcept -> double;
    auto on_mars()    const noexcept -> double;
    auto on_jupiter() const noexcept -> double;
    auto on_saturn()  const noexcept -> double;
    auto on_uranus()  const noexcept -> double;
    auto on_neptune() const noexcept -> double;

private:
    std::uint64_t m_seconds;

    /*  Seconds in one Earth year, using the exercise-specified value. */
    static constexpr double seconds_per_earth_year = 31'557'600.0;

    /*  Orbital period ratios (planet year ÷ Earth year). */
    static constexpr double mercury_ratio = 0.2408467;
    static constexpr double venus_ratio   = 0.61519726;
    static constexpr double earth_ratio   = 1.0;
    static constexpr double mars_ratio    = 1.8808158;
    static constexpr double jupiter_ratio = 11.862615;
    static constexpr double saturn_ratio  = 29.447498;
    static constexpr double uranus_ratio  = 84.016846;
    static constexpr double neptune_ratio = 164.79132;
};

}  // namespace space_age

#endif // SPACE_AGE_H
