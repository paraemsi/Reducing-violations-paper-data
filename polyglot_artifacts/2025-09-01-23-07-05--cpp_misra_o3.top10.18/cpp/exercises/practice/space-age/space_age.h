#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

using seconds_t = std::int64_t;

class space_age final {
public:
    explicit space_age(seconds_t seconds) noexcept;

    [[nodiscard]] seconds_t seconds() const noexcept;

    [[nodiscard]] double on_mercury() const noexcept;
    [[nodiscard]] double on_venus() const noexcept;
    [[nodiscard]] double on_earth() const noexcept;
    [[nodiscard]] double on_mars() const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn() const noexcept;
    [[nodiscard]] double on_uranus() const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    seconds_t m_seconds;
};

}  // namespace space_age

#endif // SPACE_AGE_H
