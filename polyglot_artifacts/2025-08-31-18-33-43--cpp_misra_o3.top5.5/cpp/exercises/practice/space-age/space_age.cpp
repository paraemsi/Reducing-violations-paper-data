#include "space_age.h"

namespace space_age {

namespace {
    /*  One Earth year is exactly 31557600 seconds (365.25 days). */
    constexpr double earth_year_seconds { 31557600.0 };

    /*  Orbital periods relative to an Earth year. */
    constexpr double mercury_period { 0.2408467 };
    constexpr double venus_period   { 0.61519726 };
    constexpr double mars_period    { 1.8808158 };
    constexpr double jupiter_period { 11.862615 };
    constexpr double saturn_period  { 29.447498 };
    constexpr double uranus_period  { 84.016846 };
    constexpr double neptune_period { 164.79132 };

    /*  Helper to compute an age on a planet from the supplied seconds. */
    constexpr double age(std::int64_t seconds, double orbital_period) noexcept
    {
        return static_cast<double>(seconds) /
               (earth_year_seconds * orbital_period);
    }
} // unnamed namespace

space_age::space_age(std::int64_t seconds) noexcept
    : m_seconds(seconds)
{
}

std::int64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_earth() const noexcept
{
    return static_cast<double>(m_seconds) / earth_year_seconds;
}

double space_age::on_mercury() const noexcept
{
    return age(m_seconds, mercury_period);
}

double space_age::on_venus() const noexcept
{
    return age(m_seconds, venus_period);
}

double space_age::on_mars() const noexcept
{
    return age(m_seconds, mars_period);
}

double space_age::on_jupiter() const noexcept
{
    return age(m_seconds, jupiter_period);
}

double space_age::on_saturn() const noexcept
{
    return age(m_seconds, saturn_period);
}

double space_age::on_uranus() const noexcept
{
    return age(m_seconds, uranus_period);
}

double space_age::on_neptune() const noexcept
{
    return age(m_seconds, neptune_period);
}

}  // namespace space_age
