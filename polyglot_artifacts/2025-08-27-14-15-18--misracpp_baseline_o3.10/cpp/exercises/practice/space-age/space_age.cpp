#include "space_age.h"

namespace space_age {

space_age::space_age(long long seconds) : seconds_{seconds} {}

long long space_age::seconds() const { return seconds_; }

double space_age::on_earth() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioEarth;
}

double space_age::on_mercury() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioMercury;
}

double space_age::on_venus() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioVenus;
}

double space_age::on_mars() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioMars;
}

double space_age::on_jupiter() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioJupiter;
}

double space_age::on_saturn() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioSaturn;
}

double space_age::on_uranus() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioUranus;
}

double space_age::on_neptune() const {
  return static_cast<double>(seconds_) / kSecondsPerEarthYear / kEarthYearRatioNeptune;
}

}  // namespace space_age
