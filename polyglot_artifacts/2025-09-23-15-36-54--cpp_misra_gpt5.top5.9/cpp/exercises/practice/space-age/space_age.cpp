#include "space_age.h"

namespace space_age {

namespace {
    constexpr double seconds_per_earth_year = 31557600.0;  // 365.25 days * 24 * 60 * 60

    constexpr double mercury_orbital = 0.2408467;
    constexpr double venus_orbital = 0.61519726;
    constexpr double earth_orbital = 1.0;
    constexpr double mars_orbital = 1.8808158;
    constexpr double jupiter_orbital = 11.862615;
    constexpr double saturn_orbital = 29.447498;
    constexpr double uranus_orbital = 84.016846;
    constexpr double neptune_orbital = 164.79132;

    inline double age_on(std::uint64_t seconds, double orbital) noexcept
    {
        return ((static_cast<double>(seconds) / seconds_per_earth_year) / orbital);
    }
}  // unnamed namespace

space_age::space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_(seconds)
{
}

std::uint64_t space_age::space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::space_age::on_earth() const noexcept
{
    return age_on(seconds_, earth_orbital);
}

double space_age::space_age::on_mercury() const noexcept
{
    return age_on(seconds_, mercury_orbital);
}

double space_age::space_age::on_venus() const noexcept
{
    return age_on(seconds_, venus_orbital);
}

double space_age::space_age::on_mars() const noexcept
{
    return age_on(seconds_, mars_orbital);
}

double space_age::space_age::on_jupiter() const noexcept
{
    return age_on(seconds_, jupiter_orbital);
}

double space_age::space_age::on_saturn() const noexcept
{
    return age_on(seconds_, saturn_orbital);
}

double space_age::space_age::on_uranus() const noexcept
{
    return age_on(seconds_, uranus_orbital);
}

double space_age::space_age::on_neptune() const noexcept
{
    return age_on(seconds_, neptune_orbital);
}

}  // namespace space_age
