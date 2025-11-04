#include "space_age.h"

namespace space_age {

space_age::space_age(std::int64_t seconds) noexcept : seconds_{seconds} {}

std::int64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::age_on(double orbital_ratio) const noexcept {
    return seconds_ / (earth_year_seconds * orbital_ratio);
}

double space_age::on_mercury() const noexcept {
    return age_on(0.2408467);
}

double space_age::on_venus() const noexcept {
    return age_on(0.61519726);
}

double space_age::on_earth() const noexcept {
    return age_on(1.0);
}

double space_age::on_mars() const noexcept {
    return age_on(1.8808158);
}

double space_age::on_jupiter() const noexcept {
    return age_on(11.862615);
}

double space_age::on_saturn() const noexcept {
    return age_on(29.447498);
}

double space_age::on_uranus() const noexcept {
    return age_on(84.016846);
}

double space_age::on_neptune() const noexcept {
    return age_on(164.79132);
}

}  // namespace space_age
