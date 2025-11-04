#if !defined(SPACE_AGE_H)
#define SPACE_AGE_H

#include <cstdint>

#if defined(__has_cpp_attribute)
#  if (__cplusplus >= 201703L) && (__has_cpp_attribute(nodiscard) >= 201603)
#    define SA_NODISCARD [[nodiscard]]
#  else
#    define SA_NODISCARD
#  endif
#else
#  if (__cplusplus >= 201703L)
#    define SA_NODISCARD [[nodiscard]]
#  else
#    define SA_NODISCARD
#  endif
#endif

namespace space_age {

class space_age {
public:
    explicit space_age(std::uint64_t seconds) noexcept;
    SA_NODISCARD std::uint64_t seconds() const noexcept;

    SA_NODISCARD double on_mercury() const noexcept;
    SA_NODISCARD double on_venus() const noexcept;
    SA_NODISCARD double on_earth() const noexcept;
    SA_NODISCARD double on_mars() const noexcept;
    SA_NODISCARD double on_jupiter() const noexcept;
    SA_NODISCARD double on_saturn() const noexcept;
    SA_NODISCARD double on_uranus() const noexcept;
    SA_NODISCARD double on_neptune() const noexcept;

private:
    std::uint64_t seconds_;
};

}  // namespace space_age

#endif // SPACE_AGE_H
