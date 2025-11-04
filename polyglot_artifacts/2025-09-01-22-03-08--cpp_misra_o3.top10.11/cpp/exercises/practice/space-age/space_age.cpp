#include "space_age.h"

namespace space_age {

space_age::space_age(std::int64_t seconds) noexcept
    : seconds_{seconds}
{
}

std::int64_t space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::on_planet(double orbital_ratio) const noexcept
{
    return ((static_cast<double>(seconds_) / seconds_per_earth_year) / orbital_ratio);
}

double space_age::on_mercury() const noexcept
{
    return on_planet(mercury_ratio);
}

double space_age::on_venus() const noexcept
{
    return on_planet(venus_ratio);
}

double space_age::on_earth() const noexcept
{
    return on_planet(earth_ratio);
}

double space_age::on_mars() const noexcept
{
    return on_planet(mars_ratio);
}

double space_age::on_jupiter() const noexcept
{
    return on_planet(jupiter_ratio);
}

double space_age::on_saturn() const noexcept
{
    return on_planet(saturn_ratio);
}

double space_age::on_uranus() const noexcept
{
    return on_planet(uranus_ratio);
}

double space_age::on_neptune() const noexcept
{
    return on_planet(neptune_ratio);
}

}  // namespace space_age
