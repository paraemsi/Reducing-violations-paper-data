#include "space_age.h"

namespace space_age {

namespace
{
    /* Orbital periods expressed in Earth years */
    constexpr double mercury_orbital_period{0.2408467};
    constexpr double venus_orbital_period{0.61519726};
    constexpr double earth_orbital_period{1.0};
    constexpr double mars_orbital_period{1.8808158};
    constexpr double jupiter_orbital_period{11.862615};
    constexpr double saturn_orbital_period{29.447498};
    constexpr double uranus_orbital_period{84.016846};
    constexpr double neptune_orbital_period{164.79132};
} // unnamed namespace

space_age::space_age(std::int64_t seconds) noexcept
    : m_seconds(seconds)
{
}

auto space_age::seconds() const noexcept -> std::int64_t
{
    return m_seconds;
}

auto space_age::on_earth() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * earth_orbital_period));
}

auto space_age::on_mercury() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * mercury_orbital_period));
}

auto space_age::on_venus() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * venus_orbital_period));
}

auto space_age::on_mars() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * mars_orbital_period));
}

auto space_age::on_jupiter() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * jupiter_orbital_period));
}

auto space_age::on_saturn() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * saturn_orbital_period));
}

auto space_age::on_uranus() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * uranus_orbital_period));
}

auto space_age::on_neptune() const noexcept -> double
{
    return (static_cast<double>(m_seconds) / (space_age::earth_year_seconds * neptune_orbital_period));
}

}  // namespace space_age
