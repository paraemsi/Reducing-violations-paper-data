#include "space_age.h"

namespace space_age {

namespace {
    constexpr double EARTH_YEAR_SECONDS = 31557600.0;
    constexpr double ORBIT_MERCURY = 0.2408467;
    constexpr double ORBIT_VENUS = 0.61519726;
    constexpr double ORBIT_EARTH = 1.0;
    constexpr double ORBIT_MARS = 1.8808158;
    constexpr double ORBIT_JUPITER = 11.862615;
    constexpr double ORBIT_SATURN = 29.447498;
    constexpr double ORBIT_URANUS = 84.016846;
    constexpr double ORBIT_NEPTUNE = 164.79132;

    inline double age_for(const std::int64_t s, const double orbital) noexcept
    {
        return (static_cast<double>(s) / (EARTH_YEAR_SECONDS * orbital));
    }
}  // namespace

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
    return (static_cast<double>(seconds_) / EARTH_YEAR_SECONDS);
}

double space_age::on_mercury() const noexcept
{
    return age_for(seconds_, ORBIT_MERCURY);
}

double space_age::on_venus() const noexcept
{
    return age_for(seconds_, ORBIT_VENUS);
}

double space_age::on_mars() const noexcept
{
    return age_for(seconds_, ORBIT_MARS);
}

double space_age::on_jupiter() const noexcept
{
    return age_for(seconds_, ORBIT_JUPITER);
}

double space_age::on_saturn() const noexcept
{
    return age_for(seconds_, ORBIT_SATURN);
}

double space_age::on_uranus() const noexcept
{
    return age_for(seconds_, ORBIT_URANUS);
}

double space_age::on_neptune() const noexcept
{
    return age_for(seconds_, ORBIT_NEPTUNE);
}

}  // namespace space_age
