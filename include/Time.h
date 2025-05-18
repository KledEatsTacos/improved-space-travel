#ifndef TIME_H
#define TIME_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Boolean.h"

struct TIME {
    int day;
    int month;
    int year;
    int hour;
    int dayLength; 
    
    void (*increaseHour)(struct TIME*);
    void (*addHours)(struct TIME*, int);
    char* (*getDate)(struct TIME*);
    char* (*getHour)(struct TIME*);
    char* (*getFullTime)(struct TIME*);
    Boolean (*dateMatches)(struct TIME*, const char*);
    int (*getDayLength)(struct TIME*);
    int (*getDaysInMonth)(struct TIME*, int, int);
    Boolean (*isLeapYear)(struct TIME*, int);
    void (*delete)(struct TIME*);
};
typedef struct TIME* Time;

Time new_Time(const char* date, int dayLength);
void Time_increaseHour(Time this);
void Time_addHours(Time this, int hours);
char* Time_getDate(Time this);
char* Time_getHour(Time this);
char* Time_getFullTime(Time this);
Boolean Time_dateMatches(Time this, const char* date);
int Time_getDayLength(Time this);
int Time_getDaysInMonth(Time this, int month, int year);
Boolean Time_isLeapYear(Time this, int year);
void delete_Time(Time this);

#endif
