#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>

// Initialisation de la structure pour les personnes
typedef struct _Person {
    int src; // étage source
    int dest; // étage destination
} Person;

// Initialisation de la structure pour les listes (chainées) de personnes
typedef struct _PersonList {
    Person *person;
    struct _PersonList *next; // pointe vers une autre adresse de case mémoire avec la prochaine personne
} PersonList;

Person* createPerson(int src, int dest);
PersonList* insert(Person *p, PersonList *list);
int lengthPersonList(PersonList *list);

#ifdef TEST

void printPerson(Person *person);
void printPersonList(PersonList *list);

#endif

#endif