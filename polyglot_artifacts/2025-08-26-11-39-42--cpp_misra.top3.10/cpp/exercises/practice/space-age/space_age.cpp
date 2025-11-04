#include "space_age.h"

namespace space_age {

    space_age::space_age(seconds_t seconds) noexcept
        : m_seconds(seconds)
    {
    }

    seconds_t space_age::seconds(void) const noexcept
    {
        return m_seconds;
    }

    double space_age::on_mercury() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * mercury_orbital));
    }

    double space_age::on_venus() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * venus_orbital));
    }

    double space_age::on_earth() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * earth_orbital));
    }

    double space_age::on_mars() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * mars_orbital));
    }

    double space_age::on_jupiter() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * jupiter_orbital));
    }

    double space_age::on_saturn() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * saturn_orbital));
    }

    double space_age::on_uranus() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * uranus_orbital));
    }

    double space_age::on_neptune() const noexcept
    {
        return (static_cast<double>(m_seconds) / (earth_year_seconds * neptune_orbital));
    }

}  // namespace space_age
