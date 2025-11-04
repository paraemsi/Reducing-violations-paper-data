#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds_in) noexcept
    : seconds_value_(seconds_in)
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return seconds_value_;
}

double space_age::on_mercury() const noexcept
{
    constexpr double mercury_period = 0.2408467;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * mercury_period);
}

double space_age::on_venus() const noexcept
{
    constexpr double venus_period = 0.61519726;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * venus_period);
}

double space_age::on_earth() const noexcept
{
    constexpr double earth_period = 1.0;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * earth_period);
}

double space_age::on_mars() const noexcept
{
    constexpr double mars_period = 1.8808158;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * mars_period);
}

double space_age::on_jupiter() const noexcept
{
    constexpr double jupiter_period = 11.862615;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * jupiter_period);
}

double space_age::on_saturn() const noexcept
{
    constexpr double saturn_period = 29.447498;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * saturn_period);
}

double space_age::on_uranus() const noexcept
{
    constexpr double uranus_period = 84.016846;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * uranus_period);
}

double space_age::on_neptune() const noexcept
{
    constexpr double neptune_period = 164.79132;
    return (static_cast<double>(seconds_value_)) /
           (earth_year_seconds * neptune_period);
}

/*  Definition of the in-class declared constant to satisfy the
 *  one-definition rule for C++14 and earlier standards.
 */
constexpr double space_age::earth_year_seconds;

} // namespace space_age
