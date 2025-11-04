#include "space_age.h"

namespace {

constexpr double seconds_per_earth_year = 31557600.0;

constexpr double mercury_period = 0.2408467;
constexpr double venus_period    = 0.61519726;
constexpr double mars_period     = 1.8808158;
constexpr double jupiter_period  = 11.862615;
constexpr double saturn_period   = 29.447498;
constexpr double uranus_period   = 84.016846;
constexpr double neptune_period  = 164.79132;

inline double age_on(const double orbital_period_in_earth_years, const space_age::seconds_t seconds) noexcept
{
    return (static_cast<double>(seconds) / (seconds_per_earth_year * orbital_period_in_earth_years));
}

}  // namespace

namespace space_age {

space_age::space_age(const seconds_t seconds) noexcept
    : seconds_(seconds)
{
}

seconds_t space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::on_earth() const noexcept
{
    return (static_cast<double>(seconds_) / seconds_per_earth_year);
}

double space_age::on_mercury() const noexcept
{
    return age_on(mercury_period, seconds_);
}

double space_age::on_venus() const noexcept
{
    return age_on(venus_period, seconds_);
}

double space_age::on_mars() const noexcept
{
    return age_on(mars_period, seconds_);
}

double space_age::on_jupiter() const noexcept
{
    return age_on(jupiter_period, seconds_);
}

double space_age::on_saturn() const noexcept
{
    return age_on(saturn_period, seconds_);
}

double space_age::on_uranus() const noexcept
{
    return age_on(uranus_period, seconds_);
}

double space_age::on_neptune() const noexcept
{
    return age_on(neptune_period, seconds_);
}

}  // namespace space_age
