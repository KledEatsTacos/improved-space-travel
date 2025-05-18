#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Boolean.h"
#include "Person.h"

typedef struct PersonList {
    Person person;
    struct PersonList* next;
} PersonListNode;

struct SPACESHIP {
    char* name;
    char* departurePlanet;
    char* destinationPlanet;
    char* departureDate;
    int travelDuration;
    int remainingTravelTime;
    PersonListNode* passengers;
    Boolean inTransit;
    Boolean destroyed;
    Boolean arrived;
    PersonListNode* originalPassengers;
    char* actualArrivalDate;
    
    void (*addPassenger)(struct SPACESHIP*, Person);
    void (*passHour)(struct SPACESHIP*);
    Boolean (*isTravelComplete)(struct SPACESHIP*);
    void (*startJourney)(struct SPACESHIP*);
    void (*endJourney)(struct SPACESHIP*);
    char* (*getName)(struct SPACESHIP*);
    char* (*getDeparturePlanet)(struct SPACESHIP*);
    char* (*getDestinationPlanet)(struct SPACESHIP*);
    char* (*getDepartureDate)(struct SPACESHIP*);
    PersonListNode* (*getPassengers)(struct SPACESHIP*);
    Boolean (*isInTransit)(struct SPACESHIP*);
    Boolean (*isDestroyed)(struct SPACESHIP*);
    Boolean (*hasArrived)(struct SPACESHIP*);
    int (*getRemainingTravelTime)(struct SPACESHIP*);
    int (*getTravelDuration)(struct SPACESHIP*);
    void (*setOriginalPassengers)(struct SPACESHIP*, PersonListNode*);
    PersonListNode* (*getOriginalPassengers)(struct SPACESHIP*);
    void (*markAsDestroyed)(struct SPACESHIP*);
    char* (*getActualArrivalDate)(struct SPACESHIP*);
    void (*setActualArrivalDate)(struct SPACESHIP*, const char*);
    char* (*toString)(struct SPACESHIP*);
    void (*delete)(struct SPACESHIP*);
};
typedef struct SPACESHIP* Spaceship;

Spaceship new_Spaceship(const char* name, const char* departurePlanet, const char* destinationPlanet, 
                         const char* departureDate, int travelDuration);
void Spaceship_addPassenger(const Spaceship this, Person person);
void Spaceship_passHour(const Spaceship this);
Boolean Spaceship_isTravelComplete(const Spaceship this);
void Spaceship_startJourney(const Spaceship this);
void Spaceship_endJourney(const Spaceship this);
char* Spaceship_getName(const Spaceship this);
char* Spaceship_getDeparturePlanet(const Spaceship this);
char* Spaceship_getDestinationPlanet(const Spaceship this);
char* Spaceship_getDepartureDate(const Spaceship this);
PersonListNode* Spaceship_getPassengers(const Spaceship this);
Boolean Spaceship_isInTransit(const Spaceship this);
Boolean Spaceship_isDestroyed(const Spaceship this);
Boolean Spaceship_hasArrived(const Spaceship this);
int Spaceship_getRemainingTravelTime(const Spaceship this);
int Spaceship_getTravelDuration(const Spaceship this);
void Spaceship_setOriginalPassengers(const Spaceship this, PersonListNode* passengers);
PersonListNode* Spaceship_getOriginalPassengers(const Spaceship this);
void Spaceship_markAsDestroyed(const Spaceship this);
char* Spaceship_getActualArrivalDate(const Spaceship this);
void Spaceship_setActualArrivalDate(const Spaceship this, const char* actualArrivalDate);
char* Spaceship_toString(const Spaceship this);
void delete_Spaceship(const Spaceship this);


PersonListNode* new_PersonListNode(Person person);
void add_PersonListNode(PersonListNode** head, Person person);
PersonListNode* copy_PersonList(PersonListNode* original);
int count_PersonList(PersonListNode* head);
void delete_PersonList(PersonListNode* head, Boolean deletePeople);
PersonListNode* filter_AlivePersons(PersonListNode* head);

#endif
