#include "space_age.h"

namespace space_age {

// Define constexpr static data members (required for non-integral types
// when compiling before C++17 and still valid for C++17+).
constexpr double space_age::earth_year_seconds;
constexpr double space_age::mercury_orbital_ratio;
constexpr double space_age::venus_orbital_ratio;
constexpr double space_age::mars_orbital_ratio;
constexpr double space_age::jupiter_orbital_ratio;
constexpr double space_age::saturn_orbital_ratio;
constexpr double space_age::uranus_orbital_ratio;
constexpr double space_age::neptune_orbital_ratio;

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_{seconds}
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::on_earth() const noexcept
{
    return static_cast<double>(seconds_) / earth_year_seconds;
}

double space_age::on_mercury() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / mercury_orbital_ratio;
}

double space_age::on_venus() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / venus_orbital_ratio;
}

double space_age::on_mars() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / mars_orbital_ratio;
}

double space_age::on_jupiter() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / jupiter_orbital_ratio;
}

double space_age::on_saturn() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / saturn_orbital_ratio;
}

double space_age::on_uranus() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / uranus_orbital_ratio;
}

double space_age::on_neptune() const noexcept
{
    const double earth_years{static_cast<double>(seconds_) / earth_year_seconds};
    return earth_years / neptune_orbital_ratio;
}

} // namespace space_age
