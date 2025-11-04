#include "space_age.h"

namespace space_age {

constexpr double space_age::earth_year_seconds;
constexpr double space_age::mercury_years;
constexpr double space_age::venus_years;
constexpr double space_age::mars_years;
constexpr double space_age::jupiter_years;
constexpr double space_age::saturn_years;
constexpr double space_age::uranus_years;
constexpr double space_age::neptune_years;

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_value(seconds) {}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_value;
}

double space_age::on_earth() const noexcept {
    return (static_cast<double>(seconds_value) / space_age::earth_year_seconds);
}

double space_age::on_mercury() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::mercury_years));
}

double space_age::on_venus() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::venus_years));
}

double space_age::on_mars() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::mars_years));
}

double space_age::on_jupiter() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::jupiter_years));
}

double space_age::on_saturn() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::saturn_years));
}

double space_age::on_uranus() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::uranus_years));
}

double space_age::on_neptune() const noexcept {
    return (static_cast<double>(seconds_value) / (space_age::earth_year_seconds * space_age::neptune_years));
}

}  // namespace space_age
