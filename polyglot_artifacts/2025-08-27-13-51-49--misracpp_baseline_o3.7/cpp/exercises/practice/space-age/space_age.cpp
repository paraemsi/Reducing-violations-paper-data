#include "space_age.h"

#include <array>

namespace space_age {

namespace {
    constexpr double earth_year_seconds = 31557600.0;

    constexpr std::array<double, 8> orbital_periods = {
        0.2408467,   // Mercury
        0.61519726,  // Venus
        1.0,         // Earth
        1.8808158,   // Mars
        11.862615,   // Jupiter
        29.447498,   // Saturn
        84.016846,   // Uranus
        164.79132    // Neptune
    };

    enum planet_index {
        mercury,
        venus,
        earth,
        mars,
        jupiter,
        saturn,
        uranus,
        neptune
    };

    // Helper
    inline double age_on(double seconds, double orbital_period) {
        return seconds / (earth_year_seconds * orbital_period);
    }
} // namespace


double space_age::on_earth() const   { return age_on(seconds_, orbital_periods[earth]);   }
double space_age::on_mercury() const { return age_on(seconds_, orbital_periods[mercury]); }
double space_age::on_venus() const   { return age_on(seconds_, orbital_periods[venus]);   }
double space_age::on_mars() const    { return age_on(seconds_, orbital_periods[mars]);    }
double space_age::on_jupiter() const { return age_on(seconds_, orbital_periods[jupiter]); }
double space_age::on_saturn()  const { return age_on(seconds_, orbital_periods[saturn]);  }
double space_age::on_uranus()  const { return age_on(seconds_, orbital_periods[uranus]);  }
double space_age::on_neptune() const { return age_on(seconds_, orbital_periods[neptune]); }

}  // namespace space_age
