#include "person.h"

// création d'une personne (étage source src et étage destination dest)
Person* createPerson(int src, int dest)
{
    Person *person = malloc(sizeof(Person));
    person->src = src;
    person->dest = dest;

    return person;
}

// insère une personne au début d'une liste de personne (données en arguments)
PersonList* insert(Person *person, PersonList *list)
{
    PersonList *newList = malloc(sizeof(PersonList));
    newList->person = person;
    newList->next = list;

    return newList;
}

// renvoie le nombre de personnes dans une liste de personnes
int lengthPersonList(PersonList *list)
{
    int length = 0;
    while(list)
    {
        length++;
        list = list->next;
    }

    return length;
}

#ifdef TEST
// fonctions inutiles pour l'exécution mais utiles pour mes tests

// affiche une liste de personnes
void printPersonList(PersonList *list)
{
    while(list)
    {
        printPerson(list->person);
        list = list->next;
    }
}

// affiche les caractéristiques d'une personne
void printPerson(Person *person)
{
    printf("Étage source : %d\nÉtage destination : %d\n\n", person->src, person->dest);
}

#endif