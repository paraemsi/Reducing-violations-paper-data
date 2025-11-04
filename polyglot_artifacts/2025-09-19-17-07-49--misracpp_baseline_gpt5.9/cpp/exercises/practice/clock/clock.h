#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute = 0);
    static clock at(int hour, int minute = 0);
    clock plus(int minutes) const;
    operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    int minutes_;
    static int normalize_minutes(int total_minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
