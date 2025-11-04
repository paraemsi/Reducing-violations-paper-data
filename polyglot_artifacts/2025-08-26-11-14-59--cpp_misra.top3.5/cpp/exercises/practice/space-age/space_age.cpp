#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds(seconds)
{
}

double space_age::seconds() const
{
    return static_cast<double>(m_seconds);
}

double space_age::on_mercury() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * mercury_orbital));
}

double space_age::on_venus() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * venus_orbital));
}

double space_age::on_earth() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * earth_orbital));
}

double space_age::on_mars() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * mars_orbital));
}

double space_age::on_jupiter() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * jupiter_orbital));
}

double space_age::on_saturn() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * saturn_orbital));
}

double space_age::on_uranus() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * uranus_orbital));
}

double space_age::on_neptune() const
{
    return (static_cast<double>(m_seconds) / (earth_year_seconds * neptune_orbital));
}

}  // namespace space_age
