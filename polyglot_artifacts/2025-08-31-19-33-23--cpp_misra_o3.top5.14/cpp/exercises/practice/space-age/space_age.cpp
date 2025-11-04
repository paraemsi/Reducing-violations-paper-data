#include "space_age.h"

namespace space_age {

constexpr double space_age::earth_year_seconds_;

space_age::space_age(std::int64_t seconds) noexcept
    : seconds_{ seconds }
{
}

std::int64_t space_age::seconds() const noexcept
{
    return seconds_;
}

namespace
{
    /* Orbital periods relative to Earth (in Earth years) */
    constexpr double mercury_orbital_period{ 0.2408467 };
    constexpr double venus_orbital_period{ 0.61519726 };
    constexpr double earth_orbital_period{ 1.0 };
    constexpr double mars_orbital_period{ 1.8808158 };
    constexpr double jupiter_orbital_period{ 11.862615 };
    constexpr double saturn_orbital_period{ 29.447498 };
    constexpr double uranus_orbital_period{ 84.016846 };
    constexpr double neptune_orbital_period{ 164.79132 };
} // unnamed namespace

double space_age::on_mercury() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * mercury_orbital_period);
}

double space_age::on_venus() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * venus_orbital_period);
}

double space_age::on_earth() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * earth_orbital_period);
}

double space_age::on_mars() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * mars_orbital_period);
}

double space_age::on_jupiter() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * jupiter_orbital_period);
}

double space_age::on_saturn() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * saturn_orbital_period);
}

double space_age::on_uranus() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * uranus_orbital_period);
}

double space_age::on_neptune() const noexcept
{
    return static_cast<double>(seconds_) / (earth_year_seconds_ * neptune_orbital_period);
}

}  // namespace space_age
