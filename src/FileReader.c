#include "../include/FileReader.h"

#define BUFFER_SIZE 8192


PlanetListNode* new_PlanetListNode(Planet planet) {
    PlanetListNode* node = (PlanetListNode*)malloc(sizeof(PlanetListNode));
    node->planet = planet;
    node->next = NULL;
    return node;
}

void add_PlanetListNode(PlanetListNode** head, Planet planet) {
    PlanetListNode* newNode = new_PlanetListNode(planet);
    if (*head == NULL) {
        *head = newNode;
    } else {
        PlanetListNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int count_PlanetList(PlanetListNode* head) {
    int count = 0;
    PlanetListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void delete_PlanetList(PlanetListNode* head, Boolean deletePlanets) {
    PlanetListNode* current = head;
    while (current != NULL) {
        PlanetListNode* next = current->next;
        if (deletePlanets == TRUE) {
            current->planet->delete(current->planet);
        }
        free(current);
        current = next;
    }
}

Planet find_PlanetByName(PlanetListNode* head, const char* name) {
    PlanetListNode* current = head;
    while (current != NULL) {
        char* planetName = current->planet->getName(current->planet);
        if (strcmp(planetName, name) == 0) {
            free(planetName);
            return current->planet;
        }
        free(planetName);
        current = current->next;
    }
    return NULL;
}


SpaceshipListNode* new_SpaceshipListNode(Spaceship spaceship) {
    SpaceshipListNode* node = (SpaceshipListNode*)malloc(sizeof(SpaceshipListNode));
    node->spaceship = spaceship;
    node->next = NULL;
    return node;
}

void add_SpaceshipListNode(SpaceshipListNode** head, Spaceship spaceship) {
    SpaceshipListNode* newNode = new_SpaceshipListNode(spaceship);
    if (*head == NULL) {
        *head = newNode;
    } else {
        SpaceshipListNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int count_SpaceshipList(SpaceshipListNode* head) {
    int count = 0;
    SpaceshipListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void delete_SpaceshipList(SpaceshipListNode* head, Boolean deleteSpaceships) {
    SpaceshipListNode* current = head;
    while (current != NULL) {
        SpaceshipListNode* next = current->next;
        if (deleteSpaceships == TRUE) {
            current->spaceship->delete(current->spaceship);
        }
        free(current);
        current = next;
    }
}

Spaceship find_SpaceshipByName(SpaceshipListNode* head, const char* name) {
    SpaceshipListNode* current = head;
    while (current != NULL) {
        char* shipName = current->spaceship->getName(current->spaceship);
        if (strcmp(shipName, name) == 0) {
            free(shipName);
            return current->spaceship;
        }
        free(shipName);
        current = current->next;
    }
    return NULL;
}


PlanetListNode* FileReader_readPlanets(const char* filePath) {
    PlanetListNode* planets = NULL;
    
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening planet file: %s\n", filePath);
        return planets;
    }
    
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {

        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') continue;
        
   
        line[strcspn(line, "\r\n")] = '\0';
        
  
        char* name = strtok(line, "#");
        char* typeStr = strtok(NULL, "#");
        char* dayLengthStr = strtok(NULL, "#");
        char* date = strtok(NULL, "#");
        
        if (name != NULL && typeStr != NULL && dayLengthStr != NULL && date != NULL) {

            while (*name == ' ') name++;
            while (*typeStr == ' ') typeStr++;
            while (*dayLengthStr == ' ') dayLengthStr++;
            while (*date == ' ') date++;
              PlanetType type = (PlanetType)atoi(typeStr);
            int dayLength = atoi(dayLengthStr);
            
 
            if (type < ROCK_PLANET || type > DWARF_PLANET) {
                fprintf(stderr, "Warning: Invalid planet type %d for planet %s. Using ROCK_PLANET as default.\n", 
                       type, name);
                type = ROCK_PLANET;
            }

            Planet planet = NULL;
            switch(type) {
                case ROCK_PLANET:
                    planet = (Planet)new_RockPlanet(name, dayLength, date);
                    break;
                case GAS_GIANT:
                    planet = (Planet)new_GasGiantPlanet(name, dayLength, date);
                    break;
                case ICE_GIANT:
                    planet = (Planet)new_IceGiantPlanet(name, dayLength, date);
                    break;
                case DWARF_PLANET:
                    planet = (Planet)new_DwarfPlanet(name, dayLength, date);
                    break;
                default:

                    planet = (Planet)new_RockPlanet(name, dayLength, date);
            }
            
            add_PlanetListNode(&planets, planet);
        } else {
            fprintf(stderr, "Warning: Invalid planet data format: %s\n", line);
        }
    }
    
    fclose(file);
    return planets;
}

SpaceshipListNode* FileReader_readSpaceships(const char* filePath) {
    SpaceshipListNode* ships = NULL;
    
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening spaceship file: %s\n", filePath);
        return ships;
    }
    
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {

        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') continue;
        

        line[strcspn(line, "\r\n")] = '\0';
        
 
        char* name = strtok(line, "#");
        char* departurePlanet = strtok(NULL, "#");
        char* destinationPlanet = strtok(NULL, "#");
        char* departureDate = strtok(NULL, "#");
        char* travelDurationStr = strtok(NULL, "#");
        
        if (name != NULL && departurePlanet != NULL && destinationPlanet != NULL && 
            departureDate != NULL && travelDurationStr != NULL) {
            

            while (*name == ' ') name++;
            while (*departurePlanet == ' ') departurePlanet++;
            while (*destinationPlanet == ' ') destinationPlanet++;
            while (*departureDate == ' ') departureDate++;
            while (*travelDurationStr == ' ') travelDurationStr++;
            
            int travelDuration = atoi(travelDurationStr);

            char normDate[11] = {0};
            int d, m, y;
            if (sscanf(departureDate, "%d.%d.%d", &d, &m, &y) == 3) {
                sprintf(normDate, "%02d.%02d.%04d", d, m, y);
            } else {

                strncpy(normDate, departureDate, sizeof(normDate)-1);
            }
            Spaceship ship = new_Spaceship(name,
                                           departurePlanet,
                                           destinationPlanet,
                                           normDate,
                                           travelDuration);
            add_SpaceshipListNode(&ships, ship);
        }
    }
    
    fclose(file);
    return ships;
}

PersonListNode* FileReader_readPeople(const char* filePath) {
    PersonListNode* people = NULL;
    
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening person file: %s\n", filePath);
        return people;
    }
    
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {

        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') continue;
        

        line[strcspn(line, "\r\n")] = '\0';
        

        char* name = strtok(line, "#");
        char* ageStr = strtok(NULL, "#");
        char* lifeRemainingStr = strtok(NULL, "#");
        char* currentVehicle = strtok(NULL, "#");
        
        if (name != NULL && ageStr != NULL && lifeRemainingStr != NULL && currentVehicle != NULL) {

            while (*name == ' ') name++;
            while (*ageStr == ' ') ageStr++;
            while (*lifeRemainingStr == ' ') lifeRemainingStr++;
            while (*currentVehicle == ' ') currentVehicle++;
            
            int age = atoi(ageStr);
            int lifeRemaining = atoi(lifeRemainingStr);
            
            Person person = new_Person(name, age, lifeRemaining, currentVehicle);
            add_PersonListNode(&people, person);
        }
    }
    
    fclose(file);
    return people;
}

void FileReader_placePeople(PersonListNode* people, PlanetListNode* planets, SpaceshipListNode* ships) {
    PersonListNode* current = people;
    
    while (current != NULL) {
        Person person = current->person;
        char* vehicleName = person->getCurrentVehicle(person);
        

        Spaceship ship = find_SpaceshipByName(ships, vehicleName);
        if (ship != NULL) {

            char* departurePlanet = ship->getDeparturePlanet(ship);
            Planet planet = find_PlanetByName(planets, departurePlanet);
            
            if (planet != NULL) {
                planet->addPerson(planet, person);

            } else {
                fprintf(stderr, "Warning: Departure planet '%s' not found for ship '%s'. Person '%s' cannot be placed.\n", 
                       departurePlanet, vehicleName, person->getName(person));
            }
            
            free(departurePlanet);
            free(vehicleName);
            current = current->next;
            continue;
        }
        

        Planet planet = find_PlanetByName(planets, vehicleName);
        if (planet != NULL) {
            planet->addPerson(planet, person);
            free(vehicleName);
            current = current->next;
            continue;
        }
        
        fprintf(stderr, "Warning: Initial location '%s' not found for person '%s'. Person ignored.\n", 
               vehicleName, person->getName(person));
        
        free(vehicleName);
        current = current->next;
    }
}
