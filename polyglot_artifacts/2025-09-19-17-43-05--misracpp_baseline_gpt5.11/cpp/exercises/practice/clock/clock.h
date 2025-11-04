#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class Clock {
public:
    static Clock at(int hour, int minute = 0);
    Clock plus(int minutes) const;
    Clock minus(int minutes) const;
    std::string str() const;
    operator std::string() const;

    bool operator==(const Clock& other) const noexcept;
    bool operator!=(const Clock& other) const noexcept;

private:
    explicit Clock(int total_minutes);
    static int normalize(int total_minutes) noexcept;
    int minutes_from_midnight_;
};


namespace clock {
Clock at(int hour, int minute = 0);
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
