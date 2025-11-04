#include "space_age.h"

namespace {
    constexpr double earth_year_seconds = 31557600.0;
    constexpr double mercury_period = 0.2408467;
    constexpr double venus_period = 0.61519726;
    constexpr double earth_period = 1.0;
    constexpr double mars_period = 1.8808158;
    constexpr double jupiter_period = 11.862615;
    constexpr double saturn_period = 29.447498;
    constexpr double uranus_period = 84.016846;
    constexpr double neptune_period = 164.79132;

    inline double years_on(std::uint64_t seconds, double period) noexcept {
        return ((static_cast<double>(seconds) / earth_year_seconds) / period);
    }
}

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_{seconds} {
}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_mercury() const noexcept {
    return years_on(seconds_, mercury_period);
}

double space_age::on_venus() const noexcept {
    return years_on(seconds_, venus_period);
}

double space_age::on_earth() const noexcept {
    return years_on(seconds_, earth_period);
}

double space_age::on_mars() const noexcept {
    return years_on(seconds_, mars_period);
}

double space_age::on_jupiter() const noexcept {
    return years_on(seconds_, jupiter_period);
}

double space_age::on_saturn() const noexcept {
    return years_on(seconds_, saturn_period);
}

double space_age::on_uranus() const noexcept {
    return years_on(seconds_, uranus_period);
}

double space_age::on_neptune() const noexcept {
    return years_on(seconds_, neptune_period);
}

}  // namespace space_age
