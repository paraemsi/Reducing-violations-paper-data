#include "space_age.h"

namespace space_age {

// Definition of static constexpr members (required for compilers that do not
// support inline variables prior to C++17).
constexpr double space_age::EARTH_YEAR_SECONDS;
constexpr double space_age::ORBIT_RATIO_MERCURY;
constexpr double space_age::ORBIT_RATIO_VENUS;
constexpr double space_age::ORBIT_RATIO_EARTH;
constexpr double space_age::ORBIT_RATIO_MARS;
constexpr double space_age::ORBIT_RATIO_JUPITER;
constexpr double space_age::ORBIT_RATIO_SATURN;
constexpr double space_age::ORBIT_RATIO_URANUS;
constexpr double space_age::ORBIT_RATIO_NEPTUNE;

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds { seconds }
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_planet(double orbital_ratio) const noexcept
{
    /*  Deliberate cast from integral to floating point to perform precise
        division; justified as required for calculation of non-integral age. */
    return (static_cast<double>(m_seconds)) /
           (EARTH_YEAR_SECONDS * orbital_ratio);
}

double space_age::on_earth() const noexcept
{
    return on_planet(ORBIT_RATIO_EARTH);
}

double space_age::on_mercury() const noexcept
{
    return on_planet(ORBIT_RATIO_MERCURY);
}

double space_age::on_venus() const noexcept
{
    return on_planet(ORBIT_RATIO_VENUS);
}

double space_age::on_mars() const noexcept
{
    return on_planet(ORBIT_RATIO_MARS);
}

double space_age::on_jupiter() const noexcept
{
    return on_planet(ORBIT_RATIO_JUPITER);
}

double space_age::on_saturn() const noexcept
{
    return on_planet(ORBIT_RATIO_SATURN);
}

double space_age::on_uranus() const noexcept
{
    return on_planet(ORBIT_RATIO_URANUS);
}

double space_age::on_neptune() const noexcept
{
    return on_planet(ORBIT_RATIO_NEPTUNE);
}

}  // namespace space_age
