#include "../include/Simulation.h"
#include <time.h>


static void clearScreen();
static void updateAllPeopleLife(const Simulation this);
static void updatePlanetStatus(const Simulation this);
static void updateShipStatus(const Simulation this);
static void processShipDeparture(const Simulation this, Spaceship ship);
static void processShipArrival(const Simulation this, Spaceship ship);
static void checkSimulationComplete(const Simulation this);
static void displayState(const Simulation this);
static char* calculateArrivalDate(const Simulation this, Spaceship ship);

Simulation new_Simulation(PlanetListNode* planets, SpaceshipListNode* ships, PersonListNode* allPeople) {
    Simulation this = (Simulation)malloc(sizeof(struct SIMULATION));
    
    this->planets = planets;
    this->ships = ships;
    this->allPeople = allPeople;
    this->hourCounter = 0;
    this->simulationComplete = FALSE;
    

    this->start = &Simulation_start;
    this->delete = &delete_Simulation;
    
    return this;
}

void Simulation_start(const Simulation this) {

    
    while (this->simulationComplete == FALSE) {
        updatePlanetStatus(this);
        updateShipStatus(this);
        checkSimulationComplete(this);
        
        clearScreen();
        displayState(this);
        
        this->hourCounter++;
    }
    
    clearScreen();
    displayState(this);
    printf("\nSimulation complete after %d hours.\n", this->hourCounter);
}

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[2J");
    fflush(stdout);
#endif
}

static void updateAllPeopleLife(const Simulation this) {
    PersonListNode* current = this->allPeople;
    while (current != NULL) {
        current->person->passHour(current->person);
        current = current->next;
    }
}

static void updatePlanetStatus(const Simulation this) {
    PlanetListNode* current = this->planets;
    while (current != NULL) {
        current->planet->passHour(current->planet);
        current = current->next;
    }
}

static void updateShipStatus(const Simulation this) {
    SpaceshipListNode* current = this->ships;
    while (current != NULL) {
        Spaceship ship = current->spaceship;
        
 
        if (!ship->isDestroyed(ship)) {
            Boolean allPassengersDead = TRUE;
            PersonListNode* originalPassengers = ship->getOriginalPassengers(ship);
            
  
            if (originalPassengers == NULL || count_PersonList(originalPassengers) == 0) {
                allPassengersDead = FALSE;
            } else {
      
                PersonListNode* current = originalPassengers;
                while (current != NULL) {
                    if (current->person->isAlive(current->person)) {
                        allPassengersDead = FALSE;
                        break;
                    }
                    current = current->next;
                }
            }
            

            if (allPassengersDead) {
                ship->markAsDestroyed(ship);
            }
        }
        
        if (ship->isDestroyed(ship) == FALSE) {
            processShipDeparture(this, ship);
            ship->passHour(ship);
            processShipArrival(this, ship);
        }
        
        current = current->next;
    }
}

static void processShipDeparture(const Simulation this, Spaceship ship) {
    if (ship->isInTransit(ship) == TRUE || ship->isDestroyed(ship) == TRUE) return;
    
    char* departurePlanetName = ship->getDeparturePlanet(ship);
    Planet departurePlanet = find_PlanetByName(this->planets, departurePlanetName);
    free(departurePlanetName);
    
    if (departurePlanet == NULL) return;
    
    char* departureDate = ship->getDepartureDate(ship);
    char* shipName = ship->getName(ship);
    
    if (departurePlanet->getTime(departurePlanet)->dateMatches(
            departurePlanet->getTime(departurePlanet), departureDate) == TRUE) {
        
        PersonListNode* passengers = departurePlanet->removePeople(departurePlanet, shipName);
        

        PersonListNode* current = passengers;
        while (current != NULL) {
            ship->addPassenger(ship, current->person);
            current = current->next;
        }
        
        ship->setOriginalPassengers(ship, passengers);
        ship->startJourney(ship);
        

        delete_PersonList(passengers, FALSE);
    }
    
    free(departureDate);
    free(shipName);
}

static void processShipArrival(const Simulation this, Spaceship ship) {
    if (ship->isTravelComplete(ship) == TRUE) {
        char* destinationPlanetName = ship->getDestinationPlanet(ship);
        Planet destinationPlanet = find_PlanetByName(this->planets, destinationPlanetName);
        free(destinationPlanetName);
        
        if (destinationPlanet != NULL) {
            PersonListNode* passengers = ship->getPassengers(ship);
            PersonListNode* current = passengers;
            
            while (current != NULL) {
                char* planetName = destinationPlanet->getName(destinationPlanet);
                current->person->setCurrentVehicle(current->person, planetName);
                free(planetName);
                
                destinationPlanet->addPerson(destinationPlanet, current->person);
                current = current->next;
            }
            
            char* arrivalDate = destinationPlanet->getTime(destinationPlanet)->getDate(
                destinationPlanet->getTime(destinationPlanet));
            ship->setActualArrivalDate(ship, arrivalDate);
            free(arrivalDate);
            
            ship->endJourney(ship);
        }
    }
}

static void checkSimulationComplete(const Simulation this) {
    this->simulationComplete = TRUE;
    
    SpaceshipListNode* current = this->ships;
    while (current != NULL) {
        Spaceship ship = current->spaceship;
        
        if (ship->isDestroyed(ship) == FALSE && ship->hasArrived(ship) == FALSE) {
            this->simulationComplete = FALSE;
            return;
        }
        
        current = current->next;
    }
}

static char* calculateArrivalDate(const Simulation this, Spaceship ship) {
    if (ship->isDestroyed(ship) == TRUE) {
        return strdup("--");
    }
    

    Boolean isEffectivelyDestroyed = FALSE;
    if (ship->hasArrived(ship) == TRUE) {
        PersonListNode* originalPassengers = ship->getOriginalPassengers(ship);
        
        if (originalPassengers != NULL) {
            Boolean allOriginalsDead = TRUE;
            PersonListNode* current = originalPassengers;
            
            while (current != NULL) {
                if (current->person->isAlive(current->person) == TRUE) {
                    allOriginalsDead = FALSE;
                    break;
                }
                current = current->next;
            }
            
            if (allOriginalsDead == TRUE && count_PersonList(originalPassengers) > 0) {
                isEffectivelyDestroyed = TRUE;
            }
        }
    }
    
    if (isEffectivelyDestroyed == TRUE) {
        return strdup("--");
    } else if (ship->hasArrived(ship) == TRUE) {
        char* arrivalDate = ship->getActualArrivalDate(ship);
        if (arrivalDate == NULL) {
            return strdup("Error");
        }
        return arrivalDate;
    } else {
        char* departurePlanetName = ship->getDeparturePlanet(ship);
        Planet departurePlanet = find_PlanetByName(this->planets, departurePlanetName);
        free(departurePlanetName);
        
        if (departurePlanet != NULL) {
            char* departureDate = ship->getDepartureDate(ship);
            int dayLength = departurePlanet->getDayLength(departurePlanet);
            Time arrivalTime = new_Time(departureDate, dayLength);
            free(departureDate);
            
            arrivalTime->addHours(arrivalTime, ship->getTravelDuration(ship));
            char* date = arrivalTime->getDate(arrivalTime);
            arrivalTime->delete(arrivalTime);
            
            return date;
        }
        
        return strdup("--");
    }
}

static void displayState(const Simulation this) {
    printf("Simulation Hour: %d\n", this->hourCounter);
    printf("Planets:\n");
    
    const int planetColumnWidth = 18; 
    printf("%-10s", "");
    PlanetListNode* planetNode = this->planets;
    while (planetNode != NULL) {
        Planet planet = planetNode->planet;
        char* name = planet->getName(planet);
        char header[25];
        sprintf(header, "--- %s ---", name);
        printf("%-*s", planetColumnWidth, header);
        free(name);
        planetNode = planetNode->next;
    }
    printf("\n");

    printf("%-10s", "Date");
    printf("  ");
    planetNode = this->planets;
    while (planetNode != NULL) {
        Planet planet = planetNode->planet;
        Time time = planet->getTime(planet);
        char* date = time->getDate(time);
        printf("%-*s", planetColumnWidth, date);
        free(date);
        planetNode = planetNode->next;
    }
    printf("\n");

    printf("%-10s", "Population");
    printf("  ");
    planetNode = this->planets;
    while (planetNode != NULL) {
        Planet planet = planetNode->planet;
        PersonListNode* population = planet->getPopulation(planet);
        int populationCount = count_PersonList(population);
        printf("%-*d", planetColumnWidth, populationCount);
        planetNode = planetNode->next;
    }
    printf("\n\n");

    printf("Spaceships:\n");
    
    printf("%-12s %-12s %-10s %-10s %-20s %-20s\n",
            "Ship Name", "Status", "Departure", "Destination", "Hours Remaining", "Arrival Date");
    
    SpaceshipListNode* shipNode = this->ships;
    while (shipNode != NULL) {
        Spaceship ship = shipNode->spaceship;
        char* shipName = ship->getName(ship);
        char* departurePlanet = ship->getDeparturePlanet(ship);
        char* destinationPlanet = ship->getDestinationPlanet(ship);
        

        char status[20];
        if (ship->isDestroyed(ship) == TRUE) {
            strcpy(status, "Destroyed");
        } else if (ship->hasArrived(ship) == TRUE) {
            strcpy(status, "Arrived");
        } else if (ship->isInTransit(ship) == TRUE) {
            strcpy(status, "In Transit");
        } else {
            strcpy(status, "Waiting");
        }

        char hoursRemainingStr[10];
        if (strcmp(status, "Destroyed") == 0) {
            strcpy(hoursRemainingStr, "--");
        } else if (strcmp(status, "Arrived") == 0) {
            strcpy(hoursRemainingStr, "0");
        } else {
            sprintf(hoursRemainingStr, "%d", ship->getRemainingTravelTime(ship));
        }

        char* arrivalDate = calculateArrivalDate(this, ship);
        
        printf("%-12s %-12s %-10s %-10s %-20s %-20s\n",
            shipName,
            status,
            departurePlanet,
            destinationPlanet,
            hoursRemainingStr,
            arrivalDate
        );
        
        free(shipName);
        free(departurePlanet);
        free(destinationPlanet);
        free(arrivalDate);
        
        shipNode = shipNode->next;
    }
}

void delete_Simulation(const Simulation this) {
    if (this == NULL) return;
    
    free(this);
}
