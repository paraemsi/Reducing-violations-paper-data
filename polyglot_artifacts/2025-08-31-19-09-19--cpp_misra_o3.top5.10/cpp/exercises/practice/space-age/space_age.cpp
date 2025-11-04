#include "space_age.h"

namespace space_age {

namespace
{
    /* Orbital periods expressed as multiples of an Earth year. */
    constexpr double mercury_factor{0.2408467};
    constexpr double venus_factor{0.61519726};
    constexpr double mars_factor{1.8808158};
    constexpr double jupiter_factor{11.862615};
    constexpr double saturn_factor{29.447498};
    constexpr double uranus_factor{84.016846};
    constexpr double neptune_factor{164.79132};
} // unnamed namespace

space_age::space_age(std::int64_t seconds) noexcept
    : seconds_{seconds}
{
}

std::int64_t space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::on_earth() const noexcept
{
    return static_cast<double>(seconds_) / space_age::earth_year_seconds_;
}

double space_age::on_mercury() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / mercury_factor;
}

double space_age::on_venus() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / venus_factor;
}

double space_age::on_mars() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / mars_factor;
}

double space_age::on_jupiter() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / jupiter_factor;
}

double space_age::on_saturn() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / saturn_factor;
}

double space_age::on_uranus() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / uranus_factor;
}

double space_age::on_neptune() const noexcept
{
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / neptune_factor;
}

} // namespace space_age
