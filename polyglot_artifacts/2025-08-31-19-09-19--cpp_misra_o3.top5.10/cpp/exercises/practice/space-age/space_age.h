#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H
#include <cstdint>

namespace space_age {

class space_age final
{
public:
    explicit space_age(std::int64_t seconds) noexcept;

    [[nodiscard]] std::int64_t seconds() const noexcept;

    [[nodiscard]] double on_earth() const noexcept;
    [[nodiscard]] double on_mercury() const noexcept;
    [[nodiscard]] double on_venus() const noexcept;
    [[nodiscard]] double on_mars() const noexcept;
    [[nodiscard]] double on_jupiter() const noexcept;
    [[nodiscard]] double on_saturn() const noexcept;
    [[nodiscard]] double on_uranus() const noexcept;
    [[nodiscard]] double on_neptune() const noexcept;

private:
    std::int64_t seconds_{0};
    static inline constexpr double earth_year_seconds_{31557600.0};
};

} // namespace space_age

#endif // SPACE_AGE_H
