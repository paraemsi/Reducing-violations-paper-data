#include "space_age.h"

namespace {

/* Constants for orbital periods expressed as multiples of an Earth year. */
constexpr double earth_year_seconds = 31557600.0;
constexpr double mercury_ratio = 0.2408467;
constexpr double venus_ratio   = 0.61519726;
constexpr double earth_ratio   = 1.0;
constexpr double mars_ratio    = 1.8808158;
constexpr double jupiter_ratio = 11.862615;
constexpr double saturn_ratio  = 29.447498;
constexpr double uranus_ratio  = 84.016846;
constexpr double neptune_ratio = 164.79132;

/* Helper function to compute age on a planet. */
static auto compute_age(std::uint64_t seconds, double ratio) noexcept -> double {
    /* Convert seconds to planet years. */
    return (static_cast<double>(seconds) / earth_year_seconds) / ratio;
}

}  // unnamed namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds(seconds) {
}

auto space_age::seconds() const noexcept -> std::uint64_t {
    return m_seconds;
}

auto space_age::on_mercury() const noexcept -> double {
    return compute_age(m_seconds, mercury_ratio);
}

auto space_age::on_venus() const noexcept -> double {
    return compute_age(m_seconds, venus_ratio);
}

auto space_age::on_earth() const noexcept -> double {
    return compute_age(m_seconds, earth_ratio);
}

auto space_age::on_mars() const noexcept -> double {
    return compute_age(m_seconds, mars_ratio);
}

auto space_age::on_jupiter() const noexcept -> double {
    return compute_age(m_seconds, jupiter_ratio);
}

auto space_age::on_saturn() const noexcept -> double {
    return compute_age(m_seconds, saturn_ratio);
}

auto space_age::on_uranus() const noexcept -> double {
    return compute_age(m_seconds, uranus_ratio);
}

auto space_age::on_neptune() const noexcept -> double {
    return compute_age(m_seconds, neptune_ratio);
}

}  // namespace space_age
