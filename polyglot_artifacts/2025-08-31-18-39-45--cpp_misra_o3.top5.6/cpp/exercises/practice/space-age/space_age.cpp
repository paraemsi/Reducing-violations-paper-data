#include "space_age.h"

#include <cstdint>

namespace {

/* Seconds in one Earth year */
constexpr double kSecondsPerEarthYear { 31'557'600.0 };

/* Orbital periods relative to an Earth year */
constexpr double kMercuryOrbitalPeriod { 0.2408467 };
constexpr double kVenusOrbitalPeriod   { 0.61519726 };
constexpr double kEarthOrbitalPeriod   { 1.0 };
constexpr double kMarsOrbitalPeriod    { 1.8808158 };
constexpr double kJupiterOrbitalPeriod { 11.862615 };
constexpr double kSaturnOrbitalPeriod  { 29.447498 };
constexpr double kUranusOrbitalPeriod  { 84.016846 };
constexpr double kNeptuneOrbitalPeriod { 164.79132 };

} // unnamed namespace

namespace space_age {

space_age::space_age(std::int64_t seconds_in) noexcept
    : m_seconds { seconds_in }
{
}

std::int64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_earth() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kEarthOrbitalPeriod));
}

double space_age::on_mercury() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kMercuryOrbitalPeriod));
}

double space_age::on_venus() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kVenusOrbitalPeriod));
}

double space_age::on_mars() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kMarsOrbitalPeriod));
}

double space_age::on_jupiter() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kJupiterOrbitalPeriod));
}

double space_age::on_saturn() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kSaturnOrbitalPeriod));
}

double space_age::on_uranus() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kUranusOrbitalPeriod));
}

double space_age::on_neptune() const noexcept
{
    return (static_cast<double>(m_seconds) / (kSecondsPerEarthYear * kNeptuneOrbitalPeriod));
}

}  // namespace space_age
