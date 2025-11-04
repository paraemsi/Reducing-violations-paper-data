#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

/*  Class that converts an age expressed in seconds to the
 *  equivalent age on the various planets of the Solar System. */
class space_age final
{
public:
    explicit space_age(std::int64_t seconds) noexcept;

    [[nodiscard]] auto seconds() const noexcept -> std::int64_t;

    [[nodiscard]] auto on_mercury() const noexcept -> double;
    [[nodiscard]] auto on_venus() const noexcept -> double;
    [[nodiscard]] auto on_earth() const noexcept -> double;
    [[nodiscard]] auto on_mars() const noexcept -> double;
    [[nodiscard]] auto on_jupiter() const noexcept -> double;
    [[nodiscard]] auto on_saturn() const noexcept -> double;
    [[nodiscard]] auto on_uranus() const noexcept -> double;
    [[nodiscard]] auto on_neptune() const noexcept -> double;

private:
    static constexpr double earth_year_seconds{31557600.0};   /* 365.25 d × 24 h × 3600 s */

    std::int64_t m_seconds;   /* age expressed in seconds */
};

}  // namespace space_age

#endif // SPACE_AGE_H
