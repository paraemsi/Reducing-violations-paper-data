#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

namespace space_age {

class space_age final {
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    [[nodiscard]] auto seconds() const noexcept -> std::uint64_t;
    [[nodiscard]] auto on_earth()   const noexcept -> double;
    [[nodiscard]] auto on_mercury() const noexcept -> double;
    [[nodiscard]] auto on_venus()   const noexcept -> double;
    [[nodiscard]] auto on_mars()    const noexcept -> double;
    [[nodiscard]] auto on_jupiter() const noexcept -> double;
    [[nodiscard]] auto on_saturn()  const noexcept -> double;
    [[nodiscard]] auto on_uranus()  const noexcept -> double;
    [[nodiscard]] auto on_neptune() const noexcept -> double;

private:
    [[nodiscard]] auto years(double orbital_period) const noexcept -> double;

    std::uint64_t seconds_{0U};
    static inline constexpr double earth_year_in_seconds{31'557'600.0};
};

}  // namespace space_age

#endif // SPACE_AGE_H
