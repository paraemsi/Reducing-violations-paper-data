#if !defined(MEETUP_H)
#define MEETUP_H

#include <string>

namespace meetup {

class scheduler {
public:
    scheduler(int year, int month);
    int day() const;
    int month() const;
    int year() const;
    
    // Teenth functions
    scheduler monteenth() const;
    scheduler tuesteenth() const;
    scheduler wednesteenth() const;
    scheduler thursteenth() const;
    scheduler friteenth() const;
    scheduler saturteenth() const;
    scheduler sunteenth() const;
    
    // First week functions
    scheduler first_monday() const;
    scheduler first_tuesday() const;
    scheduler first_wednesday() const;
    scheduler first_thursday() const;
    scheduler first_friday() const;
    scheduler first_saturday() const;
    scheduler first_sunday() const;
    
    // Second week functions
    scheduler second_monday() const;
    scheduler second_tuesday() const;
    scheduler second_wednesday() const;
    scheduler second_thursday() const;
    scheduler second_friday() const;
    scheduler second_saturday() const;
    scheduler second_sunday() const;
    
    // Third week functions
    scheduler third_monday() const;
    scheduler third_tuesday() const;
    scheduler third_wednesday() const;
    scheduler third_thursday() const;
    scheduler third_friday() const;
    scheduler third_saturday() const;
    scheduler third_sunday() const;
    
    // Fourth week functions
    scheduler fourth_monday() const;
    scheduler fourth_tuesday() const;
    scheduler fourth_wednesday() const;
    scheduler fourth_thursday() const;
    scheduler fourth_friday() const;
    scheduler fourth_saturday() const;
    scheduler fourth_sunday() const;
    
    // Last week functions
    scheduler last_monday() const;
    scheduler last_tuesday() const;
    scheduler last_wednesday() const;
    scheduler last_thursday() const;
    scheduler last_friday() const;
    scheduler last_saturday() const;
    scheduler last_sunday() const;
    
private:
    int year_;
    int month_;
    int day_;
    
    // Private constructor to set day
    scheduler(int year, int month, int day);
    
    scheduler find_nth_weekday(int target_weekday, int week_num) const;
    scheduler find_teenth_weekday(int target_weekday) const;
    scheduler find_last_weekday(int target_weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
