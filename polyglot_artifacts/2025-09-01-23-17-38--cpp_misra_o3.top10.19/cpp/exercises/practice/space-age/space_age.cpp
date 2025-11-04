#include "space_age.h"

namespace space_age {

space_age::space_age(seconds_t seconds) noexcept
    : m_seconds{seconds}
{
}

auto space_age::seconds() const noexcept -> seconds_t
{
    return m_seconds;
}

auto space_age::on_earth() const noexcept -> double
{
    return static_cast<double>(m_seconds) / seconds_per_earth_year;
}

auto space_age::on_mercury() const noexcept -> double
{
    return on_earth() / 0.2408467;
}

auto space_age::on_venus() const noexcept -> double
{
    return on_earth() / 0.61519726;
}

auto space_age::on_mars() const noexcept -> double
{
    return on_earth() / 1.8808158;
}

auto space_age::on_jupiter() const noexcept -> double
{
    return on_earth() / 11.862615;
}

auto space_age::on_saturn() const noexcept -> double
{
    return on_earth() / 29.447498;
}

auto space_age::on_uranus() const noexcept -> double
{
    return on_earth() / 84.016846;
}

auto space_age::on_neptune() const noexcept -> double
{
    return on_earth() / 164.79132;
}

// Definition of the static constexpr member (required before C++17)
constexpr double space_age::seconds_per_earth_year;

} // namespace space_age
