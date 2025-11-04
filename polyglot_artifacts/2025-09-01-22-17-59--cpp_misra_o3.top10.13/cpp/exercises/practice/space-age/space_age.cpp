#include "space_age.h"

namespace space_age {

// Constructor
space_age::space_age(const seconds_t seconds) noexcept
    : m_seconds{seconds} {}

// Public accessor
auto space_age::seconds() const noexcept -> seconds_t
{
    return m_seconds;
}

// Helper: convert seconds to planetary years
namespace {
    using seconds_t = ::space_age::space_age::seconds_t;

    constexpr double earth_year_seconds = 31'557'600.0;
    constexpr double mercury_factor = 0.2408467;
    constexpr double venus_factor   = 0.61519726;
    constexpr double earth_factor   = 1.0;
    constexpr double mars_factor    = 1.8808158;
    constexpr double jupiter_factor = 11.862615;
    constexpr double saturn_factor  = 29.447498;
    constexpr double uranus_factor  = 84.016846;
    constexpr double neptune_factor = 164.79132;

    inline auto planet_years(const seconds_t sec,
                             const double factor) noexcept -> double
    {
        return (static_cast<double>(sec)
               / (earth_year_seconds * factor));
    }
} // unnamed namespace

auto space_age::on_mercury() const noexcept -> double
{
    return planet_years(m_seconds, mercury_factor);
}

auto space_age::on_venus() const noexcept -> double
{
    return planet_years(m_seconds, venus_factor);
}

auto space_age::on_earth() const noexcept -> double
{
    return planet_years(m_seconds, earth_factor);
}

auto space_age::on_mars() const noexcept -> double
{
    return planet_years(m_seconds, mars_factor);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return planet_years(m_seconds, jupiter_factor);
}

auto space_age::on_saturn() const noexcept -> double
{
    return planet_years(m_seconds, saturn_factor);
}

auto space_age::on_uranus() const noexcept -> double
{
    return planet_years(m_seconds, uranus_factor);
}

auto space_age::on_neptune() const noexcept -> double
{
    return planet_years(m_seconds, neptune_factor);
}

}  // namespace space_age
