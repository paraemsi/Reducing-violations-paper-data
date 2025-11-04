#if !defined(MEETUP_H)
#define MEETUP_H

#include <ctime>

namespace meetup {

class scheduler {
public:
    scheduler(int year, int month);
    
    // Teenth days
    int monteenth() const;
    int tuesteenth() const;
    int wednesteenth() const;
    int thursteenth() const;
    int friteenth() const;
    int saturteenth() const;
    int sunteenth() const;
    
    // First days
    int first_monday() const;
    int first_tuesday() const;
    int first_wednesday() const;
    int first_thursday() const;
    int first_friday() const;
    int first_saturday() const;
    int first_sunday() const;
    
    // Second days
    int second_monday() const;
    int second_tuesday() const;
    int second_wednesday() const;
    int second_thursday() const;
    int second_friday() const;
    int second_saturday() const;
    int second_sunday() const;
    
    // Third days
    int third_monday() const;
    int third_tuesday() const;
    int third_wednesday() const;
    int third_thursday() const;
    int third_friday() const;
    int third_saturday() const;
    int third_sunday() const;
    
    // Fourth days
    int fourth_monday() const;
    int fourth_tuesday() const;
    int fourth_wednesday() const;
    int fourth_thursday() const;
    int fourth_friday() const;
    int fourth_saturday() const;
    int fourth_sunday() const;
    
    // Last days
    int last_monday() const;
    int last_tuesday() const;
    int last_wednesday() const;
    int last_thursday() const;
    int last_friday() const;
    int last_saturday() const;
    int last_sunday() const;
    
private:
    int find_day(const char* week, const char* day_of_week) const;
    int year_;
    int month_;
};

}  // namespace meetup

#endif // MEETUP_H
