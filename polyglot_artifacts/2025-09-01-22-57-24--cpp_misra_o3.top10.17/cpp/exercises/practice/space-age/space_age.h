#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

/*
 * Class that converts an age expressed in seconds to the
 * corresponding age on each planet of the Solar System.
 */
class space_age
{
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    auto seconds() const noexcept -> std::uint64_t;

    auto on_mercury() const noexcept -> double;
    auto on_venus()   const noexcept -> double;
    auto on_earth()   const noexcept -> double;
    auto on_mars()    const noexcept -> double;
    auto on_jupiter() const noexcept -> double;
    auto on_saturn()  const noexcept -> double;
    auto on_uranus()  const noexcept -> double;
    auto on_neptune() const noexcept -> double;

private:
    std::uint64_t m_seconds; /* Stored age in seconds (UTC) */
};

}  // namespace space_age

#endif // SPACE_AGE_H
