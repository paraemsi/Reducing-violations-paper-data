#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final {
public:
    using seconds_t = std::uint64_t;

    explicit space_age(seconds_t seconds) noexcept;

    auto seconds() const noexcept -> seconds_t;

    auto on_mercury() const noexcept -> double;
    auto on_venus()   const noexcept -> double;
    auto on_earth()   const noexcept -> double;
    auto on_mars()    const noexcept -> double;
    auto on_jupiter() const noexcept -> double;
    auto on_saturn()  const noexcept -> double;
    auto on_uranus()  const noexcept -> double;
    auto on_neptune() const noexcept -> double;

private:
    seconds_t     m_seconds;
};

}  // namespace space_age

#endif // SPACE_AGE_H
