#include "space_age.h"

#include <cstdint>

namespace {

constexpr double earth_year_seconds { 31557600.0 };

constexpr double mercury_factor { 0.2408467 };
constexpr double venus_factor   { 0.61519726 };
constexpr double earth_factor   { 1.0 };
constexpr double mars_factor    { 1.8808158 };
constexpr double jupiter_factor { 11.862615 };
constexpr double saturn_factor  { 29.447498 };
constexpr double uranus_factor  { 84.016846 };
constexpr double neptune_factor { 164.79132 };

}  // unnamed namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds_value) noexcept
    : m_seconds(seconds_value)
{
}

auto space_age::seconds() const noexcept -> std::uint64_t
{
    return m_seconds;
}

auto space_age::on_mercury() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * mercury_factor);
}

auto space_age::on_venus() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * venus_factor);
}

auto space_age::on_earth() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * earth_factor);
}

auto space_age::on_mars() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * mars_factor);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * jupiter_factor);
}

auto space_age::on_saturn() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * saturn_factor);
}

auto space_age::on_uranus() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * uranus_factor);
}

auto space_age::on_neptune() const noexcept -> double
{
    return (static_cast<double>(m_seconds)) / (earth_year_seconds * neptune_factor);
}

}  // namespace space_age
