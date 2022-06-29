#include "display.h"

void DisplayPersonList(WINDOW *win, PersonList *list, int level, int offset)
{
    while (list != NULL)
    {
        // display 25 for a person going from floor 2 to floor 5
        mvwaddch(win, level, offset, '0' + list->person->src);
        mvwaddch(win, level, offset + 1, '0' + list->person->dest);
        list = list->next;
        offset+= PERSON_WIDTH;
    }
}

void DisplayElevator(WINDOW *win, int nbFloor, Elevator *e, int offset)
{
    //Display elevator
    // [23 24 31 30 42]
 
    int level = 3*(nbFloor - e->currentFloor); // 3 lines per level
    mvwaddch(win, level, offset + 1, '[');
    DisplayPersonList(win, e->persons, level, offset + 2);
    mvwaddch(win, level, offset+2+ (PERSON_WIDTH*e->capacity), ']');
}

void DisplayBuilding(WINDOW *win, Building *b)
{
    int offset = 1;

    // display wall
    // |                |
    // |[23 24 31 30 42]| 31 32
    // |                |
    int right_wall = offset + 3 + (PERSON_WIDTH*b->elevator->capacity);
    for (int i = 0 ; i < b->nbFloor ; ++i)
    {
        int level = 3 * i + 1;
        mvwaddch(win, level, offset, '|');
        mvwaddch(win, level + 1, offset, '|');
        mvwaddch(win, level, right_wall, '|');
        mvwaddch(win, level + 1, right_wall, '|');
    }
    for (int i = offset + 1 ; i < right_wall ; i++)
    {
        mvwaddch(win, 3*(b->nbFloor)+1, i, '_');
    }

    DisplayElevator(win, b->nbFloor, b->elevator, offset);

    for(int i = 0 ; i < b->nbFloor ; i++)
    {
        int level = 3 * (b->nbFloor - i);
        DisplayPersonList(win, b->waitingLists[i], level, right_wall + 2);
    }
}