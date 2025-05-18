#include "../include/Planet.h"

double getAgingFactorForPlanetType(PlanetType type) {
    switch(type) {
        case ROCK_PLANET:
            return 1.0;    
        case GAS_GIANT:
            return 0.1;    
        case ICE_GIANT:
            return 0.5;     
        case DWARF_PLANET:
            return 0.01;   
        default:
            fprintf(stderr, "Unknown planet type: %d. Using normal aging factor.\n", type);
            return 1.0;
    }
}

Planet new_Planet(const char* name, PlanetType type, int dayLength, const char* date) {
    Planet this = (Planet)malloc(sizeof(struct PLANET));
    
    this->name = strdup(name);
    this->type = type;
    this->agingFactor = getAgingFactorForPlanetType(type);
    this->dayLength = dayLength;
    this->time = new_Time(date, dayLength);
    this->population = NULL;
    this->agingAccumulator = 0.0; 
    
   
    this->passHour = &Planet_passHour;
    this->addPerson = &Planet_addPerson;
    this->removePeople = &Planet_removePeople;
    this->getName = &Planet_getName;
    this->getType = &Planet_getType;
    this->getAgingFactor = &Planet_getAgingFactor;
    this->getDayLength = &Planet_getDayLength;
    this->getTime = &Planet_getTime;
    this->getPopulation = &Planet_getPopulation;
    this->toString = &Planet_toString;
    this->delete = &delete_Planet;
    
    return this;
}

void Planet_passHour(const Planet this) {
    this->time->increaseHour(this->time);
    

    this->agingAccumulator += this->agingFactor;
    

    int hoursToAge = (int)this->agingAccumulator;
    if (hoursToAge > 0) {

        PersonListNode* current = this->population;
        while (current != NULL) {

            for (int i = 0; i < hoursToAge; i++) {
                current->person->passHour(current->person);
            }
            current = current->next;
        }
        this->agingAccumulator -= hoursToAge;
    }
    

    PersonListNode* alivePopulation = filter_AlivePersons(this->population);
    delete_PersonList(this->population, FALSE);
    this->population = alivePopulation;
}

void Planet_addPerson(const Planet this, Person person) {
    add_PersonListNode(&this->population, person);
}

PersonListNode* Planet_removePeople(const Planet this, const char* shipName) {
    PersonListNode* passengersOnShip = NULL;
    PersonListNode* remainingPopulation = NULL;
    
    PersonListNode* current = this->population;
    while (current != NULL) {
        char* vehicleName = current->person->getCurrentVehicle(current->person);
        
        if (strcmp(vehicleName, shipName) == 0) {
            add_PersonListNode(&passengersOnShip, current->person);
        } else {
            add_PersonListNode(&remainingPopulation, current->person);
        }
        
        free(vehicleName);
        current = current->next;
    }
    

    delete_PersonList(this->population, FALSE);
    this->population = remainingPopulation;
    
    return passengersOnShip;
}

char* Planet_getName(const Planet this) {
    return strdup(this->name);
}

PlanetType Planet_getType(const Planet this) {
    return this->type;
}

double Planet_getAgingFactor(const Planet this) {
    return this->agingFactor;
}

int Planet_getDayLength(const Planet this) {
    return this->dayLength;
}

Time Planet_getTime(const Planet this) {
    return this->time;
}

PersonListNode* Planet_getPopulation(const Planet this) {
    return this->population;
}

char* Planet_toString(const Planet this) {
    int populationCount = count_PersonList(this->population);
    char* timeStr = this->time->getFullTime(this->time);
    

    const char* planetTypeStr;
    switch(this->type) {
        case ROCK_PLANET:
            planetTypeStr = "Rock";
            break;
        case GAS_GIANT:
            planetTypeStr = "Gas Giant";
            break;
        case ICE_GIANT:
            planetTypeStr = "Ice Giant";
            break;
        case DWARF_PLANET:
            planetTypeStr = "Dwarf";
            break;
        default:
            planetTypeStr = "Unknown";
    }
    
    char buffer[256];
    sprintf(buffer, "%s (%s, Time: %s, Population: %d people, Aging: %.2fx)",
            this->name, planetTypeStr, timeStr, populationCount, this->agingFactor);
    
    free(timeStr);
    
    return strdup(buffer);
}

void delete_Planet(const Planet this) {
    if (this == NULL) return;
    
    free(this->name);
    this->time->delete(this->time);
    delete_PersonList(this->population, FALSE);
    
    free(this);
}
