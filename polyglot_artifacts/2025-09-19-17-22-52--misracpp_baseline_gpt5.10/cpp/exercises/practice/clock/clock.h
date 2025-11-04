#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    static clock at(int hour, int minute = 0);

    // Add minutes (use negative values to subtract)
    clock plus(int minute) const;

    // String representation "HH:MM"
    std::string to_string() const;
    operator std::string() const { return to_string(); }

    // Equality
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(int total_minutes);
    static int normalize(int total_minutes);
    int minutes_{0};
};

}  // namespace date_independent

#endif // CLOCK_H
