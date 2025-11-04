#include "space_age.h"

namespace space_age {

namespace {

// Seconds in one Earth year.
constexpr double seconds_per_earth_year { 31'557'600.0 };

// Orbital periods relative to an Earth year.
constexpr double mercury_period { 0.2408467 };
constexpr double venus_period   { 0.61519726 };
constexpr double earth_period   { 1.0 };
constexpr double mars_period    { 1.8808158 };
constexpr double jupiter_period { 11.862615 };
constexpr double saturn_period  { 29.447498 };
constexpr double uranus_period  { 84.016846 };
constexpr double neptune_period { 164.79132 };

// Helper to calculate the age on a planet.
inline double age_on_planet(std::int64_t seconds, double period) noexcept
{
    const double seconds_as_double { static_cast<double>(seconds) };
    return seconds_as_double / (seconds_per_earth_year * period);
}

} // unnamed namespace

space_age::space_age(std::int64_t seconds) noexcept
    : m_seconds{ seconds }
{
}

std::int64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_mercury() const noexcept
{
    return age_on_planet(m_seconds, mercury_period);
}

double space_age::on_venus() const noexcept
{
    return age_on_planet(m_seconds, venus_period);
}

double space_age::on_earth() const noexcept
{
    return age_on_planet(m_seconds, earth_period);
}

double space_age::on_mars() const noexcept
{
    return age_on_planet(m_seconds, mars_period);
}

double space_age::on_jupiter() const noexcept
{
    return age_on_planet(m_seconds, jupiter_period);
}

double space_age::on_saturn() const noexcept
{
    return age_on_planet(m_seconds, saturn_period);
}

double space_age::on_uranus() const noexcept
{
    return age_on_planet(m_seconds, uranus_period);
}

double space_age::on_neptune() const noexcept
{
    return age_on_planet(m_seconds, neptune_period);
}

}  // namespace space_age
