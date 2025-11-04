#include "space_age.h"

namespace space_age {

constexpr double seconds_per_earth_year{ 31'557'600.0 };

constexpr double mercury_orbital_period{ 0.2408467 };
constexpr double venus_orbital_period{ 0.61519726 };
constexpr double mars_orbital_period{ 1.8808158 };
constexpr double jupiter_orbital_period{ 11.862615 };
constexpr double saturn_orbital_period{ 29.447498 };
constexpr double uranus_orbital_period{ 84.016846 };
constexpr double neptune_orbital_period{ 164.79132 };

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds{ seconds }
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_earth() const noexcept
{
    // MISRA compliance: explicit cast from integral to floating is unavoidable here
    // to perform accurate fractional‐year calculations.
    return (static_cast<double>(m_seconds) / seconds_per_earth_year);
}

double space_age::on_mercury() const noexcept
{
    return (on_earth() / mercury_orbital_period);
}

double space_age::on_venus() const noexcept
{
    return (on_earth() / venus_orbital_period);
}

double space_age::on_mars() const noexcept
{
    return (on_earth() / mars_orbital_period);
}

double space_age::on_jupiter() const noexcept
{
    return (on_earth() / jupiter_orbital_period);
}

double space_age::on_saturn() const noexcept
{
    return (on_earth() / saturn_orbital_period);
}

double space_age::on_uranus() const noexcept
{
    return (on_earth() / uranus_orbital_period);
}

double space_age::on_neptune() const noexcept
{
    return (on_earth() / neptune_orbital_period);
}

}  // namespace space_age
