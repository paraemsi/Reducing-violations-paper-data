#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept : seconds_{seconds} {}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::age_on(double orbital_period) const noexcept {
    const double years_on_earth = (static_cast<double>(seconds_) / earth_year_seconds());
    return (years_on_earth / orbital_period);
}

double space_age::on_earth() const noexcept {
    return age_on(orbital_period_earth());
}

double space_age::on_mercury() const noexcept {
    return age_on(orbital_period_mercury());
}

double space_age::on_venus() const noexcept {
    return age_on(orbital_period_venus());
}

double space_age::on_mars() const noexcept {
    return age_on(orbital_period_mars());
}

double space_age::on_jupiter() const noexcept {
    return age_on(orbital_period_jupiter());
}

double space_age::on_saturn() const noexcept {
    return age_on(orbital_period_saturn());
}

double space_age::on_uranus() const noexcept {
    return age_on(orbital_period_uranus());
}

double space_age::on_neptune() const noexcept {
    return age_on(orbital_period_neptune());
}

}  // namespace space_age
