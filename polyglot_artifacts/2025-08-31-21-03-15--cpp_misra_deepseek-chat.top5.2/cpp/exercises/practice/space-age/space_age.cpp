#include "space_age.h"
#include <cstdint>

namespace space_age {

space_age::space_age(age_seconds_int_t seconds) : age_seconds(seconds) {}

age_seconds_int_t space_age::seconds() const {
    return age_seconds;
}

double space_age::on_mercury() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 0.2408467;
}

double space_age::on_venus() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 0.61519726;
}

double space_age::on_earth() const {
    return static_cast<double>(age_seconds) / 31557600.0;
}

double space_age::on_mars() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 1.8808158;
}

double space_age::on_jupiter() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 11.862615;
}

double space_age::on_saturn() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 29.447498;
}

double space_age::on_uranus() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 84.016846;
}

double space_age::on_neptune() const {
    return (static_cast<double>(age_seconds) / 31557600.0) / 164.79132;
}

}  // namespace space_age
