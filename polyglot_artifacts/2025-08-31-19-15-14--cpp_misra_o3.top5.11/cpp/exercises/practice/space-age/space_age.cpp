#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds{seconds}
{
    /* Constructor body intentionally left empty */
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::age_on(double orbital_period) const noexcept
{
    /* Calculate age in Earth years first, then divide by planet period */
    return (static_cast<double>(m_seconds) / earth_year_seconds) / orbital_period;
}

double space_age::on_mercury() const noexcept
{
    return age_on(mercury_period);
}

double space_age::on_venus() const noexcept
{
    return age_on(venus_period);
}

double space_age::on_earth() const noexcept
{
    return age_on(earth_period);
}

double space_age::on_mars() const noexcept
{
    return age_on(mars_period);
}

double space_age::on_jupiter() const noexcept
{
    return age_on(jupiter_period);
}

double space_age::on_saturn() const noexcept
{
    return age_on(saturn_period);
}

double space_age::on_uranus() const noexcept
{
    return age_on(uranus_period);
}

double space_age::on_neptune() const noexcept
{
    return age_on(neptune_period);
}

}  // namespace space_age
