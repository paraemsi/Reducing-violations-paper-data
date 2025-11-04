#include "space_age.h"

namespace space_age {

// Out-of-class definitions for static constexpr members (needed for C++14)
constexpr double space_age::seconds_per_earth_year;
constexpr double space_age::mercury_period;
constexpr double space_age::venus_period;
constexpr double space_age::earth_period;
constexpr double space_age::mars_period;
constexpr double space_age::jupiter_period;
constexpr double space_age::saturn_period;
constexpr double space_age::uranus_period;
constexpr double space_age::neptune_period;

space_age::space_age(long long seconds) noexcept
    : seconds_{seconds} {}

long long space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_earth() const noexcept {
    return seconds_ / (seconds_per_earth_year * earth_period);
}

double space_age::on_mercury() const noexcept {
    return seconds_ / (seconds_per_earth_year * mercury_period);
}

double space_age::on_venus() const noexcept {
    return seconds_ / (seconds_per_earth_year * venus_period);
}

double space_age::on_mars() const noexcept {
    return seconds_ / (seconds_per_earth_year * mars_period);
}

double space_age::on_jupiter() const noexcept {
    return seconds_ / (seconds_per_earth_year * jupiter_period);
}

double space_age::on_saturn() const noexcept {
    return seconds_ / (seconds_per_earth_year * saturn_period);
}

double space_age::on_uranus() const noexcept {
    return seconds_ / (seconds_per_earth_year * uranus_period);
}

double space_age::on_neptune() const noexcept {
    return seconds_ / (seconds_per_earth_year * neptune_period);
}

}  // namespace space_age
