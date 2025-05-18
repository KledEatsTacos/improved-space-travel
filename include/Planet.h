#ifndef PLANET_H
#define PLANET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Boolean.h"
#include "Person.h"
#include "Time.h"
#include "Spaceship.h"


typedef enum {
    ROCK_PLANET = 0,  
    GAS_GIANT = 1,     
    ICE_GIANT = 2,    
    DWARF_PLANET = 3 
} PlanetType;

struct PLANET {
    char* name;
    PlanetType type;
    double agingFactor; 
    int dayLength;
    Time time;
    PersonListNode* population;
    double agingAccumulator;
    
    void (*passHour)(struct PLANET*);
    void (*addPerson)(struct PLANET*, Person);
    PersonListNode* (*removePeople)(struct PLANET*, const char*);
    char* (*getName)(struct PLANET*);
    PlanetType (*getType)(struct PLANET*);
    double (*getAgingFactor)(struct PLANET*);
    int (*getDayLength)(struct PLANET*);
    Time (*getTime)(struct PLANET*);
    PersonListNode* (*getPopulation)(struct PLANET*);
    char* (*toString)(struct PLANET*);
    void (*delete)(struct PLANET*);
};
typedef struct PLANET* Planet;

Planet new_Planet(const char* name, PlanetType type, int dayLength, const char* date);
void Planet_passHour(const Planet this);
void Planet_addPerson(const Planet this, Person person);
PersonListNode* Planet_removePeople(const Planet this, const char* shipName);
char* Planet_getName(const Planet this);
PlanetType Planet_getType(const Planet this);
double Planet_getAgingFactor(const Planet this);
int Planet_getDayLength(const Planet this);
Time Planet_getTime(const Planet this);
PersonListNode* Planet_getPopulation(const Planet this);
char* Planet_toString(const Planet this);
void delete_Planet(const Planet this);


double getAgingFactorForPlanetType(PlanetType type);

#endif
