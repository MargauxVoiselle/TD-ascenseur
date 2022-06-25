#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "person.h"

// Initialisation de la structure de l'ascenseur
typedef struct _Elevator {
    int capacity; // capacité maximale de la cabine
    int currentFloor; // étage actuel
    int targetFloor; // destination
    PersonList *persons; // personnes dans la cabine
} Elevator;

// Initialisation de l'immeuble
typedef struct _Building {
    int nbFloor; // nombre d’étages de l’immeuble
    Elevator *elevator; // la cabine d’ascenseur
    PersonList **waitingLists; // tableau de listes d'attente (une par étage)
} Building;

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons);
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists);

PersonList *exitElevator(Elevator *elevator);
PersonList* enterElevator(Elevator *elevator, PersonList *list);
void stepElevator(Building *building);

#endif
