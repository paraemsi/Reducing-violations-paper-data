#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <string>

namespace meetup {

struct Date {
    std::int32_t year;
    std::int32_t month;
    std::int32_t day;
};

class scheduler {
public:
    scheduler(std::int32_t year, std::int32_t month);
    
    // Teenth days
    Date monteenth() const;
    Date tuesteenth() const;
    Date wednesteenth() const;
    Date thursteenth() const;
    Date friteenth() const;
    Date saturteenth() const;
    Date sunteenth() const;
    
    // First, second, third, fourth, last days
    Date first_monday() const;
    Date first_tuesday() const;
    Date first_wednesday() const;
    Date first_thursday() const;
    Date first_friday() const;
    Date first_saturday() const;
    Date first_sunday() const;
    
    Date second_monday() const;
    Date second_tuesday() const;
    Date second_wednesday() const;
    Date second_thursday() const;
    Date second_friday() const;
    Date second_saturday() const;
    Date second_sunday() const;
    
    Date third_monday() const;
    Date third_tuesday() const;
    Date third_wednesday() const;
    Date third_thursday() const;
    Date third_friday() const;
    Date third_saturday() const;
    Date third_sunday() const;
    
    Date fourth_monday() const;
    Date fourth_tuesday() const;
    Date fourth_wednesday() const;
    Date fourth_thursday() const;
    Date fourth_friday() const;
    Date fourth_saturday() const;
    Date fourth_sunday() const;
    
    Date last_monday() const;
    Date last_tuesday() const;
    Date last_wednesday() const;
    Date last_thursday() const;
    Date last_friday() const;
    Date last_saturday() const;
    Date last_sunday() const;
    
private:
    std::int32_t year_;
    std::int32_t month_;
    Date find_nth_weekday(const std::string& weekday, std::int32_t n) const;
    Date find_teenth(const std::string& weekday) const;
    Date find_last(const std::string& weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
