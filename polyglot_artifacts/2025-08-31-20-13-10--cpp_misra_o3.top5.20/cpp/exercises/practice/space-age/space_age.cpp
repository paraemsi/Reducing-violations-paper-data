#include "space_age.h"

namespace
{

constexpr double earth_year_seconds   = 31'557'600.0;

constexpr double mercury_orbital_period = 0.2408467;
constexpr double venus_orbital_period   = 0.61519726;
constexpr double mars_orbital_period    = 1.8808158;
constexpr double jupiter_orbital_period = 11.862615;
constexpr double saturn_orbital_period  = 29.447498;
constexpr double uranus_orbital_period  = 84.016846;
constexpr double neptune_orbital_period = 164.79132;

} // unnamed namespace

namespace space_age
{

space_age::space_age(second_t seconds_in) : m_seconds(seconds_in)
{
}

second_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::seconds_in_earth_years() const noexcept
{
    return (static_cast<double>(m_seconds) / earth_year_seconds);
}

double space_age::on_earth() const noexcept
{
    return seconds_in_earth_years();
}

double space_age::on_mercury() const noexcept
{
    return (seconds_in_earth_years() / mercury_orbital_period);
}

double space_age::on_venus() const noexcept
{
    return (seconds_in_earth_years() / venus_orbital_period);
}

double space_age::on_mars() const noexcept
{
    return (seconds_in_earth_years() / mars_orbital_period);
}

double space_age::on_jupiter() const noexcept
{
    return (seconds_in_earth_years() / jupiter_orbital_period);
}

double space_age::on_saturn() const noexcept
{
    return (seconds_in_earth_years() / saturn_orbital_period);
}

double space_age::on_uranus() const noexcept
{
    return (seconds_in_earth_years() / uranus_orbital_period);
}

double space_age::on_neptune() const noexcept
{
    return (seconds_in_earth_years() / neptune_orbital_period);
}

} // namespace space_age
