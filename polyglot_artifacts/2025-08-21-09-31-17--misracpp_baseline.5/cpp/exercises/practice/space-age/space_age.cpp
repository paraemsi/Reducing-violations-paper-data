#include "space_age.h"

namespace space_age {

space_age::space_age(long seconds) : seconds_(seconds) {}

long space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_earth() const noexcept {
    return seconds_ / earth_year_seconds;
}

double space_age::on_mercury() const noexcept {
    return on_earth() / 0.2408467;
}

double space_age::on_venus() const noexcept {
    return on_earth() / 0.61519726;
}

double space_age::on_mars() const noexcept {
    return on_earth() / 1.8808158;
}

double space_age::on_jupiter() const noexcept {
    return on_earth() / 11.862615;
}

double space_age::on_saturn() const noexcept {
    return on_earth() / 29.447498;
}

double space_age::on_uranus() const noexcept {
    return on_earth() / 84.016846;
}

double space_age::on_neptune() const noexcept {
    return on_earth() / 164.79132;
}

}  // namespace space_age
