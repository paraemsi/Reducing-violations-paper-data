#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock {
public:
    // Construct a clock at the specified hour and minute.
    // A two-argument call is required to avoid ambiguity with the
    // private single-parameter constructor.
    Clock(std::int32_t hour,
          std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    // Factory: create a clock at the specified hour and minute (default 0).
    static Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    // Return a new clock advanced by the given minutes.
    Clock plus(std::int32_t minute) const noexcept;

    // Return a new clock rewound by the given minutes.
    Clock minus(std::int32_t minute) const noexcept;

    // Return time in "HH:MM" format.
    std::string to_string() const;

    // Implicit conversion to std::string for convenience in tests.
    operator std::string() const;

    // Symmetrical comparison operators (non-member friends as per MISRA).
    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;

private:
    explicit Clock(std::int32_t total_minutes) noexcept;

    std::int32_t m_minutes; // minutes since 00:00, range [0, 1439]

    static constexpr std::int32_t MINUTES_PER_DAY =
        static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60);
};

using clock = Clock; // Provide lowercase alias expected by tests.

}  // namespace date_independent

#endif // CLOCK_H
