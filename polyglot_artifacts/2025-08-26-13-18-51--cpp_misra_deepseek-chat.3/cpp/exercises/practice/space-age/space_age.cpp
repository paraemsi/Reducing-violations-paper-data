#include "space_age.h"
#include <cmath>

namespace space_age {

space_age::space_age(double seconds) : age_seconds(seconds) {}

double space_age::seconds() const {
    return age_seconds;
}

double space_age::on_earth() const {
    return age_seconds / 31557600.0;
}

double space_age::on_mercury() const {
    return age_seconds / (0.2408467 * 31557600.0);
}

double space_age::on_venus() const {
    return age_seconds / (0.61519726 * 31557600.0);
}

double space_age::on_mars() const {
    return age_seconds / (1.8808158 * 31557600.0);
}

double space_age::on_jupiter() const {
    return age_seconds / (11.862615 * 31557600.0);
}

double space_age::on_saturn() const {
    return age_seconds / (29.447498 * 31557600.0);
}

double space_age::on_uranus() const {
    return age_seconds / (84.016846 * 31557600.0);
}

double space_age::on_neptune() const {
    return age_seconds / (164.79132 * 31557600.0);
}

}  // namespace space_age
