#include "space_age.h"

namespace space_age {

namespace {
    constexpr double earth_year_seconds{31557600.0};

    constexpr double mercury_ratio{0.2408467};
    constexpr double venus_ratio{0.61519726};
    constexpr double earth_ratio{1.0};
    constexpr double mars_ratio{1.8808158};
    constexpr double jupiter_ratio{11.862615};
    constexpr double saturn_ratio{29.447498};
    constexpr double uranus_ratio{84.016846};
    constexpr double neptune_ratio{164.79132};
}

space_age::space_age(long long seconds) : _seconds{seconds} {}

long long space_age::seconds() const noexcept {
    return _seconds;
}

double space_age::on_earth() const noexcept {
    return _seconds / (earth_year_seconds * earth_ratio);
}

double space_age::on_mercury() const {
    return _seconds / (earth_year_seconds * mercury_ratio);
}

double space_age::on_venus() const {
    return _seconds / (earth_year_seconds * venus_ratio);
}

double space_age::on_mars() const {
    return _seconds / (earth_year_seconds * mars_ratio);
}

double space_age::on_jupiter() const {
    return _seconds / (earth_year_seconds * jupiter_ratio);
}

double space_age::on_saturn() const {
    return _seconds / (earth_year_seconds * saturn_ratio);
}

double space_age::on_uranus() const {
    return _seconds / (earth_year_seconds * uranus_ratio);
}

double space_age::on_neptune() const noexcept {
    return _seconds / (earth_year_seconds * neptune_ratio);
}

}  // namespace space_age
