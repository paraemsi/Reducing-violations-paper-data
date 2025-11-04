#include "space_age.h"

namespace
{
    constexpr double mercury_ratio  = 0.2408467;
    constexpr double venus_ratio    = 0.61519726;
    constexpr double mars_ratio     = 1.8808158;
    constexpr double jupiter_ratio  = 11.862615;
    constexpr double saturn_ratio   = 29.447498;
    constexpr double uranus_ratio   = 84.016846;
    constexpr double neptune_ratio  = 164.79132;
} // unnamed namespace

namespace space_age {

space_age::space_age(std::int64_t seconds) noexcept
    : m_seconds{seconds}
{
}

std::int64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_earth() const noexcept
{
    return static_cast<double>(m_seconds) / space_age::earth_year_seconds;
}

double space_age::on_mercury() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / mercury_ratio;
}

double space_age::on_venus() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / venus_ratio;
}

double space_age::on_mars() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / mars_ratio;
}

double space_age::on_jupiter() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / jupiter_ratio;
}

double space_age::on_saturn() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / saturn_ratio;
}

double space_age::on_uranus() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / uranus_ratio;
}

double space_age::on_neptune() const noexcept
{
    return (static_cast<double>(m_seconds) / space_age::earth_year_seconds) / neptune_ratio;
}

}  // namespace space_age

// Definition of the static constexpr data member.
// Required for non-integral static constexpr prior to C++17.
constexpr double space_age::space_age::earth_year_seconds;
