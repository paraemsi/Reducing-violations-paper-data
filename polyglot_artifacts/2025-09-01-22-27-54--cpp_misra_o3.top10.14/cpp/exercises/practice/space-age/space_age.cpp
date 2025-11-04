#include "space_age.h"

namespace
{
    /* 31 557 600 seconds in one Earth year (365.25 days) */
    constexpr double k_seconds_per_earth_year { 31'557'600.0 };

    /* Orbital periods expressed in Earth years */
    constexpr double k_orbital_mercury { 0.2408467 };
    constexpr double k_orbital_venus   { 0.61519726 };
    constexpr double k_orbital_mars    { 1.8808158 };
    constexpr double k_orbital_jupiter { 11.862615 };
    constexpr double k_orbital_saturn  { 29.447498 };
    constexpr double k_orbital_uranus  { 84.016846 };
    constexpr double k_orbital_neptune { 164.79132 };
} // unnamed namespace

namespace space_age {

space_age::space_age(seconds_t seconds) noexcept
    : m_seconds{ seconds }
{
}

seconds_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_earth() const noexcept
{
    return static_cast<double>(m_seconds) / k_seconds_per_earth_year;
}

double space_age::on_mercury() const noexcept
{
    return (on_earth()) / k_orbital_mercury;
}

double space_age::on_venus() const noexcept
{
    return (on_earth()) / k_orbital_venus;
}

double space_age::on_mars() const noexcept
{
    return (on_earth()) / k_orbital_mars;
}

double space_age::on_jupiter() const noexcept
{
    return (on_earth()) / k_orbital_jupiter;
}

double space_age::on_saturn() const noexcept
{
    return (on_earth()) / k_orbital_saturn;
}

double space_age::on_uranus() const noexcept
{
    return (on_earth()) / k_orbital_uranus;
}

double space_age::on_neptune() const noexcept
{
    return (on_earth()) / k_orbital_neptune;
}

}  // namespace space_age
