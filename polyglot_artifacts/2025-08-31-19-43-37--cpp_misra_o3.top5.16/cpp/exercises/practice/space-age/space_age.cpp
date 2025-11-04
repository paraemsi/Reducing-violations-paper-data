#include "space_age.h"

#include <cstdint>

namespace space_age {

// Definitions of static constexpr data members (required for C++14 linkage)
constexpr double space_age::earth_year_in_seconds;
constexpr double space_age::mercury_orbital_period;
constexpr double space_age::venus_orbital_period;
constexpr double space_age::mars_orbital_period;
constexpr double space_age::jupiter_orbital_period;
constexpr double space_age::saturn_orbital_period;
constexpr double space_age::uranus_orbital_period;
constexpr double space_age::neptune_orbital_period;

space_age::space_age(std::int64_t seconds) noexcept
    : seconds_{seconds}
{
}

std::int64_t space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::age_on_planet(double orbital_period) const noexcept
{
    return (static_cast<double>(seconds_)) /
           (orbital_period * space_age::earth_year_in_seconds);
}

double space_age::on_mercury() const noexcept
{
    return age_on_planet(space_age::mercury_orbital_period);
}

double space_age::on_venus() const noexcept
{
    return age_on_planet(space_age::venus_orbital_period);
}

double space_age::on_earth() const noexcept
{
    return age_on_planet(1.0);
}

double space_age::on_mars() const noexcept
{
    return age_on_planet(space_age::mars_orbital_period);
}

double space_age::on_jupiter() const noexcept
{
    return age_on_planet(space_age::jupiter_orbital_period);
}

double space_age::on_saturn() const noexcept
{
    return age_on_planet(space_age::saturn_orbital_period);
}

double space_age::on_uranus() const noexcept
{
    return age_on_planet(space_age::uranus_orbital_period);
}

double space_age::on_neptune() const noexcept
{
    return age_on_planet(space_age::neptune_orbital_period);
}

}  // namespace space_age
