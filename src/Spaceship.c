#include "../include/Spaceship.h"


PersonListNode* new_PersonListNode(Person person) {
    PersonListNode* node = (PersonListNode*)malloc(sizeof(PersonListNode));
    node->person = person;
    node->next = NULL;
    return node;
}

void add_PersonListNode(PersonListNode** head, Person person) {
    PersonListNode* newNode = new_PersonListNode(person);
    if (*head == NULL) {
        *head = newNode;
    } else {
        PersonListNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

PersonListNode* copy_PersonList(PersonListNode* original) {
    if (original == NULL) return NULL;
    
    PersonListNode* newHead = NULL;
    PersonListNode* current = original;
    
    while (current != NULL) {
        add_PersonListNode(&newHead, current->person);
        current = current->next;
    }
    
    return newHead;
}

int count_PersonList(PersonListNode* head) {
    int count = 0;
    PersonListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void delete_PersonList(PersonListNode* head, Boolean deletePeople) {
    PersonListNode* current = head;
    while (current != NULL) {
        PersonListNode* next = current->next;
        if (deletePeople == TRUE) {
            current->person->delete(current->person);
        }
        free(current);
        current = next;
    }
}

PersonListNode* filter_AlivePersons(PersonListNode* head) {
    PersonListNode* newHead = NULL;
    PersonListNode* current = head;
    
    while (current != NULL) {
        if (current->person->isAlive(current->person) == TRUE) {
            add_PersonListNode(&newHead, current->person);
        }
        current = current->next;
    }
    
    return newHead;
}


Spaceship new_Spaceship(const char* name, const char* departurePlanet, const char* destinationPlanet, 
                        const char* departureDate, int travelDuration) {
    Spaceship this = (Spaceship)malloc(sizeof(struct SPACESHIP));
    
    this->name = strdup(name);
    this->departurePlanet = strdup(departurePlanet);
    this->destinationPlanet = strdup(destinationPlanet);
    this->departureDate = strdup(departureDate);
    this->travelDuration = travelDuration;
    this->remainingTravelTime = travelDuration;
    this->passengers = NULL;
    this->inTransit = FALSE;
    this->destroyed = FALSE;
    this->arrived = FALSE;
    this->originalPassengers = NULL;
    this->actualArrivalDate = NULL;
    

    this->addPassenger = &Spaceship_addPassenger;
    this->passHour = &Spaceship_passHour;
    this->isTravelComplete = &Spaceship_isTravelComplete;
    this->startJourney = &Spaceship_startJourney;
    this->endJourney = &Spaceship_endJourney;
    this->getName = &Spaceship_getName;
    this->getDeparturePlanet = &Spaceship_getDeparturePlanet;
    this->getDestinationPlanet = &Spaceship_getDestinationPlanet;
    this->getDepartureDate = &Spaceship_getDepartureDate;
    this->getPassengers = &Spaceship_getPassengers;
    this->isInTransit = &Spaceship_isInTransit;
    this->isDestroyed = &Spaceship_isDestroyed;
    this->hasArrived = &Spaceship_hasArrived;
    this->getRemainingTravelTime = &Spaceship_getRemainingTravelTime;
    this->getTravelDuration = &Spaceship_getTravelDuration;
    this->setOriginalPassengers = &Spaceship_setOriginalPassengers;
    this->getOriginalPassengers = &Spaceship_getOriginalPassengers;
    this->markAsDestroyed = &Spaceship_markAsDestroyed;
    this->getActualArrivalDate = &Spaceship_getActualArrivalDate;
    this->setActualArrivalDate = &Spaceship_setActualArrivalDate;
    this->toString = &Spaceship_toString;
    this->delete = &delete_Spaceship;
    
    return this;
}

void Spaceship_addPassenger(const Spaceship this, Person person) {
    add_PersonListNode(&this->passengers, person);
}

void Spaceship_passHour(const Spaceship this) {

    if (this->inTransit == TRUE) {
        PersonListNode* current = this->passengers;
        while (current != NULL) {
            current->person->passHour(current->person);
            current = current->next;
        }
    }
    
    if (this->inTransit == TRUE && this->destroyed == FALSE) {
        this->remainingTravelTime--;
        
        Boolean hadPassengers = (this->passengers != NULL);
        

        PersonListNode* alivePassengers = filter_AlivePersons(this->passengers);
        delete_PersonList(this->passengers, FALSE); 
        this->passengers = alivePassengers;
        
        if (this->passengers == NULL && hadPassengers == TRUE) {
            this->destroyed = TRUE;
        }
    }
}

Boolean Spaceship_isTravelComplete(const Spaceship this) {
    return (this->inTransit == TRUE && this->remainingTravelTime <= 0) ? TRUE : FALSE;
}

void Spaceship_startJourney(const Spaceship this) {
    this->inTransit = TRUE;
}

void Spaceship_endJourney(const Spaceship this) {
    this->inTransit = FALSE;
    this->arrived = TRUE;
}

char* Spaceship_getName(const Spaceship this) {
    return strdup(this->name);
}

char* Spaceship_getDeparturePlanet(const Spaceship this) {
    return strdup(this->departurePlanet);
}

char* Spaceship_getDestinationPlanet(const Spaceship this) {
    return strdup(this->destinationPlanet);
}

char* Spaceship_getDepartureDate(const Spaceship this) {
    return strdup(this->departureDate);
}

PersonListNode* Spaceship_getPassengers(const Spaceship this) {
    return this->passengers;
}

Boolean Spaceship_isInTransit(const Spaceship this) {
    return this->inTransit;
}

Boolean Spaceship_isDestroyed(const Spaceship this) {
    return this->destroyed;
}

Boolean Spaceship_hasArrived(const Spaceship this) {
    return this->arrived;
}

int Spaceship_getRemainingTravelTime(const Spaceship this) {
    return this->remainingTravelTime;
}

int Spaceship_getTravelDuration(const Spaceship this) {
    return this->travelDuration;
}

void Spaceship_setOriginalPassengers(const Spaceship this, PersonListNode* passengers) {
    if (this->originalPassengers != NULL) {
        delete_PersonList(this->originalPassengers, FALSE);
    }
    this->originalPassengers = copy_PersonList(passengers);
}

PersonListNode* Spaceship_getOriginalPassengers(const Spaceship this) {
    return this->originalPassengers;
}

void Spaceship_markAsDestroyed(const Spaceship this) {
    this->destroyed = TRUE;
}

char* Spaceship_getActualArrivalDate(const Spaceship this) {
    return (this->actualArrivalDate != NULL) ? strdup(this->actualArrivalDate) : NULL;
}

void Spaceship_setActualArrivalDate(const Spaceship this, const char* actualArrivalDate) {
    if (this->actualArrivalDate != NULL) {
        free(this->actualArrivalDate);
    }
    this->actualArrivalDate = (actualArrivalDate != NULL) ? strdup(actualArrivalDate) : NULL;
}

char* Spaceship_toString(const Spaceship this) {
    char buffer[256];
    int passengerCount = count_PersonList(this->passengers);
    
    if (this->destroyed == TRUE) {
        sprintf(buffer, "%s (DESTROYED)", this->name);
    } else if (this->inTransit == TRUE) {
        sprintf(buffer, "%s (%s -> %s, Time remaining: %d hours, Passengers: %d)",
                this->name, this->departurePlanet, this->destinationPlanet, 
                this->remainingTravelTime, passengerCount);
    } else if (this->arrived == TRUE) {
        sprintf(buffer, "%s (Arrived at %s, Passengers: %d)",
                this->name, this->destinationPlanet, passengerCount);
    } else {
        sprintf(buffer, "%s (On planet %s, Passengers: %d)",
                this->name, this->departurePlanet, passengerCount);
    }
    
    return strdup(buffer);
}

void delete_Spaceship(const Spaceship this) {
    if (this == NULL) return;
    
    free(this->name);
    free(this->departurePlanet);
    free(this->destinationPlanet);
    free(this->departureDate);
    
    if (this->actualArrivalDate != NULL) {
        free(this->actualArrivalDate);
    }
    
    delete_PersonList(this->passengers, FALSE);
    
    if (this->originalPassengers != NULL) {
        delete_PersonList(this->originalPassengers, FALSE);
    }
    
    free(this);
}
