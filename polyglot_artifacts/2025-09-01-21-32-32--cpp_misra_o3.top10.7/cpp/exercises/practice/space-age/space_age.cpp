#include "space_age.h"

namespace space_age {


space_age::space_age(const std::uint64_t seconds) noexcept
    : seconds_{seconds}
{
}

auto space_age::seconds() const noexcept -> std::uint64_t
{
    return seconds_;
}

auto space_age::years(const double orbital_period) const noexcept -> double
{
    return static_cast<double>(seconds_) / (earth_year_in_seconds * orbital_period);
}

auto space_age::on_earth() const noexcept -> double
{
    return years(1.0);
}

auto space_age::on_mercury() const noexcept -> double
{
    return years(0.2408467);
}

auto space_age::on_venus() const noexcept -> double
{
    return years(0.61519726);
}

auto space_age::on_mars() const noexcept -> double
{
    return years(1.8808158);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return years(11.862615);
}

auto space_age::on_saturn() const noexcept -> double
{
    return years(29.447498);
}

auto space_age::on_uranus() const noexcept -> double
{
    return years(84.016846);
}

auto space_age::on_neptune() const noexcept -> double
{
    return years(164.79132);
}

}  // namespace space_age
