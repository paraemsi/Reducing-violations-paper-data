#include "space_age.h"
#include <cmath>

namespace space_age {

space_age::space_age(double seconds) : age_in_seconds(seconds) {}

double space_age::seconds() const {
    return age_in_seconds;
}

double space_age::on_earth() const {
    return age_in_seconds / 31557600.0;
}

double space_age::on_mercury() const {
    return age_in_seconds / (31557600.0 * 0.2408467);
}

double space_age::on_venus() const {
    return age_in_seconds / (31557600.0 * 0.61519726);
}

double space_age::on_mars() const {
    return age_in_seconds / (31557600.0 * 1.8808158);
}

double space_age::on_jupiter() const {
    return age_in_seconds / (31557600.0 * 11.862615);
}

double space_age::on_saturn() const {
    return age_in_seconds / (31557600.0 * 29.447498);
}

double space_age::on_uranus() const {
    return age_in_seconds / (31557600.0 * 84.016846);
}

double space_age::on_neptune() const {
    return age_in_seconds / (31557600.0 * 164.79132);
}

}  // namespace space_age
