#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H
#include <cstdint>

#if (__cplusplus >= 201703L)
#define EXERCISM_NODISCARD [[nodiscard]]
#else
#define EXERCISM_NODISCARD
#endif

namespace space_age {

class space_age final
{
public:
    explicit space_age(std::uint64_t seconds) noexcept;

    EXERCISM_NODISCARD std::uint64_t seconds() const noexcept;

    EXERCISM_NODISCARD double on_earth() const noexcept;
    EXERCISM_NODISCARD double on_mercury() const noexcept;
    EXERCISM_NODISCARD double on_venus() const noexcept;
    EXERCISM_NODISCARD double on_mars() const noexcept;
    EXERCISM_NODISCARD double on_jupiter() const noexcept;
    EXERCISM_NODISCARD double on_saturn() const noexcept;
    EXERCISM_NODISCARD double on_uranus() const noexcept;
    EXERCISM_NODISCARD double on_neptune() const noexcept;

private:
    std::uint64_t m_seconds;
};

}  // namespace space_age

#endif // SPACE_AGE_H
