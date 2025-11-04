#include "space_age.h"

namespace space_age {

/* Out-of-class definitions for static constexpr data members
 * (required for C++14 linkage) */
constexpr double space_age::earth_year_seconds;
constexpr double space_age::mercury_ratio;
constexpr double space_age::venus_ratio;
constexpr double space_age::earth_ratio;
constexpr double space_age::mars_ratio;
constexpr double space_age::jupiter_ratio;
constexpr double space_age::saturn_ratio;
constexpr double space_age::uranus_ratio;
constexpr double space_age::neptune_ratio;

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds(seconds)
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_mercury() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * mercury_ratio));
}

double space_age::on_venus() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * venus_ratio));
}

double space_age::on_earth() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * earth_ratio));
}

double space_age::on_mars() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * mars_ratio));
}

double space_age::on_jupiter() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * jupiter_ratio));
}

double space_age::on_saturn() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * saturn_ratio));
}

double space_age::on_uranus() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * uranus_ratio));
}

double space_age::on_neptune() const noexcept
{
    return (static_cast<double>(m_seconds) /
            (earth_year_seconds * neptune_ratio));
}

}  // namespace space_age
