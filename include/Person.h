#ifndef PERSON_H
#define PERSON_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Boolean.h"

struct PERSON {
    char* name;
    int age;
    int lifeRemaining;
    char* currentVehicle;
    
    void (*passHour)(struct PERSON*);
    Boolean (*isAlive)(struct PERSON*);
    char* (*getName)(struct PERSON*);
    int (*getAge)(struct PERSON*);
    int (*getLifeRemaining)(struct PERSON*);
    char* (*getCurrentVehicle)(struct PERSON*);
    void (*setCurrentVehicle)(struct PERSON*, const char*);
    char* (*toString)(struct PERSON*);
    void (*delete)(struct PERSON*);
};
typedef struct PERSON* Person;

Person new_Person(const char* name, int age, int lifeRemaining, const char* currentVehicle);
void Person_passHour(const Person this);
Boolean Person_isAlive(const Person this);
char* Person_getName(const Person this);
int Person_getAge(const Person this);
int Person_getLifeRemaining(const Person this);
char* Person_getCurrentVehicle(const Person this);
void Person_setCurrentVehicle(const Person this, const char* currentVehicle);
char* Person_toString(const Person this);
void delete_Person(const Person this);

#endif
