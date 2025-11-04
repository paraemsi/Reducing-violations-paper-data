#include "space_age.h"

namespace space_age {

namespace {
    // Orbital periods in Earth years
    constexpr double mercury_period = 0.2408467;
    constexpr double venus_period   = 0.61519726;
    constexpr double earth_period   = 1.0;
    constexpr double mars_period    = 1.8808158;
    constexpr double jupiter_period = 11.862615;
    constexpr double saturn_period  = 29.447498;
    constexpr double uranus_period  = 84.016846;
    constexpr double neptune_period = 164.79132;
}

space_age::space_age(seconds_t seconds) noexcept
    : m_seconds(seconds)
{
}

double space_age::seconds() const noexcept
{
    return static_cast<double>(m_seconds);
}

double space_age::on_mercury() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * mercury_period));
}

double space_age::on_venus() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * venus_period));
}

double space_age::on_earth() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * earth_period));
}

double space_age::on_mars() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * mars_period));
}

double space_age::on_jupiter() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * jupiter_period));
}

double space_age::on_saturn() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * saturn_period));
}

double space_age::on_uranus() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * uranus_period));
}

double space_age::on_neptune() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * neptune_period));
}

}  // namespace space_age
