#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds)
    : m_seconds(seconds)
{
}

std::uint64_t space_age::seconds() const
{
    return m_seconds;
}

double space_age::on_mercury() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 0.2408467));
}

double space_age::on_venus() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 0.61519726));
}

double space_age::on_earth() const
{
    return (static_cast<double>(m_seconds) / earth_year_seconds);
}

double space_age::on_mars() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 1.8808158));
}

double space_age::on_jupiter() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 11.862615));
}

double space_age::on_saturn() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 29.447498));
}

double space_age::on_uranus() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 84.016846));
}

double space_age::on_neptune() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * 164.79132));
}

}  // namespace space_age
