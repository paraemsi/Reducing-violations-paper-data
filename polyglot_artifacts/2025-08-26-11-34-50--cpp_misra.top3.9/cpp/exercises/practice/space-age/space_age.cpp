#include "space_age.h"

namespace space_age {

    // Orbital periods in Earth years (as per instructions)
    namespace {
        constexpr double earth_year_seconds = 31557600.0;
        constexpr double mercury_orbital = 0.2408467;
        constexpr double venus_orbital   = 0.61519726;
        constexpr double earth_orbital   = 1.0;
        constexpr double mars_orbital    = 1.8808158;
        constexpr double jupiter_orbital = 11.862615;
        constexpr double saturn_orbital  = 29.447498;
        constexpr double uranus_orbital  = 84.016846;
        constexpr double neptune_orbital = 164.79132;
    }

    space_age::space_age(seconds_t seconds) noexcept
        : m_seconds(seconds)
    {
    }

    std::int64_t space_age::seconds() const noexcept
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
