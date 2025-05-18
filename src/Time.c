#include "../include/Time.h"

Time new_Time(const char* date, int dayLength) {
    Time this = (Time)malloc(sizeof(struct TIME));
    

    char* dateCopy = strdup(date);
    char* day_str = strtok(dateCopy, ".");
    char* month_str = strtok(NULL, ".");
    char* year_str = strtok(NULL, ".");
    
    this->day = atoi(day_str);
    this->month = atoi(month_str);
    this->year = atoi(year_str);
    this->hour = 0;
    this->dayLength = dayLength;
    
    free(dateCopy);
    

    this->increaseHour = &Time_increaseHour;
    this->addHours = &Time_addHours;
    this->getDate = &Time_getDate;
    this->getHour = &Time_getHour;
    this->getFullTime = &Time_getFullTime;
    this->dateMatches = &Time_dateMatches;
    this->getDayLength = &Time_getDayLength;
    this->getDaysInMonth = &Time_getDaysInMonth;
    this->isLeapYear = &Time_isLeapYear;
    this->delete = &delete_Time;
    
    return this;
}

Boolean Time_isLeapYear(Time this, int year) {

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return TRUE;
    }
    return FALSE;
}

int Time_getDaysInMonth(Time this, int month, int year) {

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    

    if (month == 2 && this->isLeapYear(this, year)) {
        return 29;
    }
    

    if (month < 1 || month > 12) {
        fprintf(stderr, "Error: Invalid month %d\n", month);
        return 30;
    }
    
    return daysInMonth[month];
}

void Time_increaseHour(const Time this) {
    this->hour++;
    if (this->hour >= this->dayLength) {
        this->hour = 0;
        this->day++;
        
        int daysInCurrentMonth = this->getDaysInMonth(this, this->month, this->year);
        
        if (this->day > daysInCurrentMonth) {
            this->day = 1;
            this->month++;
            
            if (this->month > 12) {
                this->month = 1;
                this->year++;
            }
        }
    }
}

void Time_addHours(const Time this, int hours) {
    int totalHours = this->hour + hours;
    
    int daysToAdd = totalHours / this->dayLength;
    
    this->hour = totalHours % this->dayLength;
    
    for (int i = 0; i < daysToAdd; i++) {
        this->day++;
        int daysInCurrentMonth = this->getDaysInMonth(this, this->month, this->year);
        
        if (this->day > daysInCurrentMonth) {
            this->day = 1;
            this->month++;
            
            if (this->month > 12) {
                this->month = 1;
                this->year++;
            }
        }
    }
}

char* Time_getDate(const Time this) {
    char* result = (char*)malloc(11); 
    sprintf(result, "%02d.%02d.%d", this->day, this->month, this->year);
    return result;
}

char* Time_getHour(const Time this) {
    char* result = (char*)malloc(6); 
    sprintf(result, "%02d:00", this->hour);
    return result;
}

char* Time_getFullTime(const Time this) {
    char* date = Time_getDate(this);
    char* hour = Time_getHour(this);
    
    char* result = (char*)malloc(strlen(date) + strlen(hour) + 2); 
    sprintf(result, "%s %s", date, hour);
    
    free(date);
    free(hour);
    
    return result;
}

Boolean Time_dateMatches(const Time this, const char* date) {
    char* thisDate = Time_getDate(this);
    Boolean result = (strcmp(thisDate, date) == 0) ? TRUE : FALSE;
    free(thisDate);
    return result;
}

int Time_getDayLength(const Time this) {
    return this->dayLength;
}

void delete_Time(const Time this) {
    if (this == NULL) return;
    free(this);
}
