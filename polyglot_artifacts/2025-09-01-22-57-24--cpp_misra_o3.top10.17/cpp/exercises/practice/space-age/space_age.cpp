#include "space_age.h"

namespace
{
    /* Constant: number of seconds in one Earth year (365.25 days). */
    constexpr double seconds_per_earth_year{ 31'557'600.0 };

    /* Planet–to–Earth orbital period ratios. */
    constexpr double mercury_year_ratio{ 0.2408467 };
    constexpr double venus_year_ratio{   0.61519726 };
    constexpr double earth_year_ratio{   1.0 };
    constexpr double mars_year_ratio{    1.8808158 };
    constexpr double jupiter_year_ratio{ 11.862615 };
    constexpr double saturn_year_ratio{  29.447498 };
    constexpr double uranus_year_ratio{  84.016846 };
    constexpr double neptune_year_ratio{ 164.79132 };

    /* Helper that performs the common conversion. */
    inline auto to_planet_years(std::uint64_t seconds,
                                double        planet_ratio) noexcept -> double
    {
        /* Explicit cast avoids implicit integral-to-floating conversion. */
        return (static_cast<double>(seconds)) /
               (seconds_per_earth_year * planet_ratio);
    }
} // unnamed namespace

namespace space_age {

space_age::space_age(const std::uint64_t seconds) noexcept
    : m_seconds{ seconds }
{
}

auto space_age::seconds() const noexcept -> std::uint64_t
{
    return m_seconds;
}

auto space_age::on_mercury() const noexcept -> double
{
    return to_planet_years(m_seconds, mercury_year_ratio);
}

auto space_age::on_venus() const noexcept -> double
{
    return to_planet_years(m_seconds, venus_year_ratio);
}

auto space_age::on_earth() const noexcept -> double
{
    return to_planet_years(m_seconds, earth_year_ratio);
}

auto space_age::on_mars() const noexcept -> double
{
    return to_planet_years(m_seconds, mars_year_ratio);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return to_planet_years(m_seconds, jupiter_year_ratio);
}

auto space_age::on_saturn() const noexcept -> double
{
    return to_planet_years(m_seconds, saturn_year_ratio);
}

auto space_age::on_uranus() const noexcept -> double
{
    return to_planet_years(m_seconds, uranus_year_ratio);
}

auto space_age::on_neptune() const noexcept -> double
{
    return to_planet_years(m_seconds, neptune_year_ratio);
}

}  // namespace space_age
