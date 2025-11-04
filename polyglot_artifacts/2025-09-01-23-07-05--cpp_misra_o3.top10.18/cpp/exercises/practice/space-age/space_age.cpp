#include "space_age.h"

namespace space_age {

namespace {
    constexpr double earth_year_seconds = 31557600.0;
    constexpr double mercury_factor = 0.2408467;
    constexpr double venus_factor   = 0.61519726;
    constexpr double earth_factor   = 1.0;
    constexpr double mars_factor    = 1.8808158;
    constexpr double jupiter_factor = 11.862615;
    constexpr double saturn_factor  = 29.447498;
    constexpr double uranus_factor  = 84.016846;
    constexpr double neptune_factor = 164.79132;

    inline double age_in_years(seconds_t sec, double orbital_factor) noexcept
    {
        return (static_cast<double>(sec) / earth_year_seconds) / orbital_factor;
    }
} // unnamed namespace

space_age::space_age(seconds_t seconds) noexcept
    : m_seconds(seconds)
{
}

seconds_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_mercury() const noexcept
{
    return age_in_years(m_seconds, mercury_factor);
}

double space_age::on_venus() const noexcept
{
    return age_in_years(m_seconds, venus_factor);
}

double space_age::on_earth() const noexcept
{
    return age_in_years(m_seconds, earth_factor);
}

double space_age::on_mars() const noexcept
{
    return age_in_years(m_seconds, mars_factor);
}

double space_age::on_jupiter() const noexcept
{
    return age_in_years(m_seconds, jupiter_factor);
}

double space_age::on_saturn() const noexcept
{
    return age_in_years(m_seconds, saturn_factor);
}

double space_age::on_uranus() const noexcept
{
    return age_in_years(m_seconds, uranus_factor);
}

double space_age::on_neptune() const noexcept
{
    return age_in_years(m_seconds, neptune_factor);
}

}  // namespace space_age
