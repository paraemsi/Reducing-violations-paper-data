#include "space_age.h"
#include <cmath>

namespace space_age {

space_age::space_age(double seconds) : age_seconds(seconds) {}

double space_age::seconds() const {
    return age_seconds;
}

#include <cmath>
#include <iomanip>
#include <sstream>

double space_age::on_earth() const {
    return std::round((age_seconds / 31557600.0) * 100) / 100;
}

double space_age::on_mercury() const {
    return std::round((on_earth() / 0.2408467) * 100) / 100;
}

double space_age::on_venus() const {
    return std::round((on_earth() / 0.61519726) * 100) / 100;
}

double space_age::on_mars() const {
    return std::round((on_earth() / 1.8808158) * 100) / 100;
}

double space_age::on_jupiter() const {
    return std::round((on_earth() / 11.862615) * 100) / 100;
}

double space_age::on_saturn() const {
    return std::round((on_earth() / 29.447498) * 100) / 100;
}

double space_age::on_uranus() const {
    return std::round((on_earth() / 84.016846) * 100) / 100;
}

double space_age::on_neptune() const {
    return std::round((on_earth() / 164.79132) * 100) / 100;
}

}  // namespace space_age
