#include "space_age.h"

namespace space_age {

static const double kEarthYearSeconds = 31557600.0;

space_age::space_age(std::uint64_t seconds) : seconds_(seconds) {}

std::uint64_t space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return seconds_ / kEarthYearSeconds;
}

double space_age::on_mercury() const {
    return seconds_ / (kEarthYearSeconds * 0.2408467);
}

double space_age::on_venus() const {
    return seconds_ / (kEarthYearSeconds * 0.61519726);
}

double space_age::on_mars() const {
    return seconds_ / (kEarthYearSeconds * 1.8808158);
}

double space_age::on_jupiter() const {
    return seconds_ / (kEarthYearSeconds * 11.862615);
}

double space_age::on_saturn() const {
    return seconds_ / (kEarthYearSeconds * 29.447498);
}

double space_age::on_uranus() const {
    return seconds_ / (kEarthYearSeconds * 84.016846);
}

double space_age::on_neptune() const {
    return seconds_ / (kEarthYearSeconds * 164.79132);
}

}  // namespace space_age
