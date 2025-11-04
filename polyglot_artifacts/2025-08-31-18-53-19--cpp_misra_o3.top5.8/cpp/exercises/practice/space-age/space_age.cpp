#include "space_age.h"

#include <cstdint>

namespace space_age {

namespace
{
    /*  Seconds in one Earth year, as specified by the exercise. */
    static constexpr double seconds_per_earth_year = 31'557'600.0;
    /*  Helper that converts an age in seconds to planet-specific years.   */
    auto age_on_planet(std::uint64_t seconds, double ratio) noexcept -> double
    {
        return (
            static_cast<double>(seconds) /
            (seconds_per_earth_year * ratio)
        );
    }
}   // unnamed namespace

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds(seconds)
{
}

auto space_age::seconds() const noexcept -> std::uint64_t
{
    return m_seconds;
}

auto space_age::on_earth() const noexcept -> double
{
    return age_on_planet(m_seconds, earth_ratio);
}

auto space_age::on_mercury() const noexcept -> double
{
    return age_on_planet(m_seconds, mercury_ratio);
}

auto space_age::on_venus() const noexcept -> double
{
    return age_on_planet(m_seconds, venus_ratio);
}

auto space_age::on_mars() const noexcept -> double
{
    return age_on_planet(m_seconds, mars_ratio);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return age_on_planet(m_seconds, jupiter_ratio);
}

auto space_age::on_saturn() const noexcept -> double
{
    return age_on_planet(m_seconds, saturn_ratio);
}

auto space_age::on_uranus() const noexcept -> double
{
    return age_on_planet(m_seconds, uranus_ratio);
}

auto space_age::on_neptune() const noexcept -> double
{
    return age_on_planet(m_seconds, neptune_ratio);
}

}  // namespace space_age
