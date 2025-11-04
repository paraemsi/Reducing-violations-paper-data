#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds(seconds)
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_earth() const noexcept
{
    return (static_cast<double>(m_seconds) / earth_year_seconds);
}

double space_age::on_mercury() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 0.2408467));
}

double space_age::on_venus() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 0.61519726));
}

double space_age::on_mars() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 1.8808158));
}

double space_age::on_jupiter() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 11.862615));
}

double space_age::on_saturn() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 29.447498));
}

double space_age::on_uranus() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 84.016846));
}

double space_age::on_neptune() const noexcept
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 164.79132));
}

}  // namespace space_age
