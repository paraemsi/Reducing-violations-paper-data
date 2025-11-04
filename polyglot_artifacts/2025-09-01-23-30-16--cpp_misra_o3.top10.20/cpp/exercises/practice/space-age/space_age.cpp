#include "space_age.h"
#include <cstdint>

namespace {

/* Seconds in one Earth year */
constexpr double k_seconds_per_earth_year { 31'557'600.0 };

/* Orbital periods relative to Earth years */
constexpr double k_orbital_mercury { 0.2408467 };
constexpr double k_orbital_venus   { 0.61519726 };
constexpr double k_orbital_mars    { 1.8808158 };
constexpr double k_orbital_jupiter { 11.862615 };
constexpr double k_orbital_saturn  { 29.447498 };
constexpr double k_orbital_uranus  { 84.016846 };
constexpr double k_orbital_neptune { 164.79132 };

/* Helper: convert seconds to Earth years */
auto age_on_earth(std::uint64_t seconds) noexcept -> double
{
    return (static_cast<double>(seconds) / k_seconds_per_earth_year);
}

} // unnamed namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds{ seconds }
{
}

auto space_age::seconds() const noexcept -> std::uint64_t
{
    return m_seconds;
}

auto space_age::on_mercury() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_mercury);
}

auto space_age::on_venus() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_venus);
}

auto space_age::on_earth() const noexcept -> double
{
    return age_on_earth(m_seconds);
}

auto space_age::on_mars() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_mars);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_jupiter);
}

auto space_age::on_saturn() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_saturn);
}

auto space_age::on_uranus() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_uranus);
}

auto space_age::on_neptune() const noexcept -> double
{
    return (age_on_earth(m_seconds) / k_orbital_neptune);
}

} // namespace space_age
