#include "space_age.h"

namespace space_age {
/* Out-of-class definition required for constexpr static data member
 * (pre-C++17, the member is not implicitly inline). */
constexpr double space_age::earth_year_seconds;
} // namespace space_age


namespace {

    /* Orbital periods relative to an Earth year */
    static constexpr double mercury_factor = 0.2408467;
    static constexpr double venus_factor   = 0.61519726;
    static constexpr double mars_factor    = 1.8808158;
    static constexpr double jupiter_factor = 11.862615;
    static constexpr double saturn_factor  = 29.447498;
    static constexpr double uranus_factor  = 84.016846;
    static constexpr double neptune_factor = 164.79132;

    static double age_in_earth_years(const std::int64_t seconds) noexcept
    {
        /* Explicit cast to satisfy MISRA rule regarding category mixing */
        return static_cast<double>(seconds) / space_age::space_age::earth_year_seconds;
    }

} // unnamed namespace

namespace space_age {

space_age::space_age(std::int64_t seconds) noexcept
    : m_seconds(seconds)
{
}

std::int64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_mercury() const noexcept
{
    return (age_in_earth_years(m_seconds)) / mercury_factor;
}

double space_age::on_venus() const noexcept
{
    return (age_in_earth_years(m_seconds)) / venus_factor;
}

double space_age::on_earth() const noexcept
{
    return age_in_earth_years(m_seconds);
}

double space_age::on_mars() const noexcept
{
    return (age_in_earth_years(m_seconds)) / mars_factor;
}

double space_age::on_jupiter() const noexcept
{
    return (age_in_earth_years(m_seconds)) / jupiter_factor;
}

double space_age::on_saturn() const noexcept
{
    return (age_in_earth_years(m_seconds)) / saturn_factor;
}

double space_age::on_uranus() const noexcept
{
    return (age_in_earth_years(m_seconds)) / uranus_factor;
}

double space_age::on_neptune() const noexcept
{
    return (age_in_earth_years(m_seconds)) / neptune_factor;
}

}  // namespace space_age
