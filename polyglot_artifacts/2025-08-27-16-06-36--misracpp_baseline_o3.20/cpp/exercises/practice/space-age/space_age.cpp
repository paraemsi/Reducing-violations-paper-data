#include "space_age.h"

namespace space_age {

const double space_age::earth_year_seconds = 31557600.0;

space_age::space_age(uint64_t seconds) : seconds_{seconds} {}

uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_earth() const noexcept {
    return seconds_ / earth_year_seconds;
}

double space_age::on_mercury() const noexcept {
    return seconds_ / (earth_year_seconds * 0.2408467);
}

double space_age::on_venus() const noexcept {
    return seconds_ / (earth_year_seconds * 0.61519726);
}

double space_age::on_mars() const noexcept {
    return seconds_ / (earth_year_seconds * 1.8808158);
}

double space_age::on_jupiter() const noexcept {
    return seconds_ / (earth_year_seconds * 11.862615);
}

double space_age::on_saturn() const noexcept {
    return seconds_ / (earth_year_seconds * 29.447498);
}

double space_age::on_uranus() const noexcept {
    return seconds_ / (earth_year_seconds * 84.016846);
}

double space_age::on_neptune() const noexcept {
    return seconds_ / (earth_year_seconds * 164.79132);
}

}  // namespace space_age
