#include "micromouse.h"
#include "maze.h"

void turn_best_neighor(uint8_t best_neighbor)
{
  /*Get current heading*/
  uint8_t heading = mouse_get_heading();
  /*Relative positioning to best neighbor*/
  int8_t delta = heading - best_neighbor;

  /*Truth table to find how much we need to turn*/
  switch(delta)
  {
    case 7: case -1: case -2: case -4:
      /*Physically turn the mouse*/
      control_turn(-90.0);
      break;
    case -7: case 1: case 2: case 4:
      /*Physically turn the mouse*/
      control_turn(90.0);
      break;
    case 3: case -3: case 6: case -6:
      /*Physically turn the mouse*/
      control_turn(180.0);
      break;  
  }

  /*Update heading mouse*/
  mouse_set_heading(best_neighbor);
}