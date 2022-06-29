#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include "person.h"
#include "elevator.h"

#define HEIGHT 30
#define WIDTH 40
#define PERSON_WIDTH 3


void DisplayPersonList(WINDOW *win, PersonList *list, int level, int offset);
void DisplayElevator(WINDOW *win, int nbFloor, Elevator *e, int offset);
void DisplayBuilding(WINDOW *win, Building *b);

#endif