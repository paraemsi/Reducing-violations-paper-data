#include "space_age.h"

namespace space_age {

namespace {
static constexpr double earth_year_seconds = 31'557'600.0;
/* Helper to compute age in years on a planet.
 * All arguments are floating-point to avoid category-mixing assignments.
 */
[[nodiscard]] auto age_in_years(const std::int64_t seconds,
                                const double orbital_ratio) noexcept -> double
{
    /* static_cast used deliberately to convert integral to floating as per MISRA
     * rule on unavoidable conversion.
     */
    return (static_cast<double>(seconds)) /
           (earth_year_seconds * orbital_ratio);
}
} // unnamed namespace

space_age::space_age(std::int64_t seconds) noexcept
    : seconds_{seconds}
{
}

auto space_age::seconds() const noexcept -> std::int64_t
{
    return seconds_;
}

auto space_age::on_earth() const noexcept -> double
{
    return age_in_years(seconds_, 1.0);
}

auto space_age::on_mercury() const noexcept -> double
{
    return age_in_years(seconds_, mercury_orbital_ratio);
}

auto space_age::on_venus() const noexcept -> double
{
    return age_in_years(seconds_, venus_orbital_ratio);
}

auto space_age::on_mars() const noexcept -> double
{
    return age_in_years(seconds_, mars_orbital_ratio);
}

auto space_age::on_jupiter() const noexcept -> double
{
    return age_in_years(seconds_, jupiter_orbital_ratio);
}

auto space_age::on_saturn() const noexcept -> double
{
    return age_in_years(seconds_, saturn_orbital_ratio);
}

auto space_age::on_uranus() const noexcept -> double
{
    return age_in_years(seconds_, uranus_orbital_ratio);
}

auto space_age::on_neptune() const noexcept -> double
{
    return age_in_years(seconds_, neptune_orbital_ratio);
}

}  // namespace space_age
