#include "micromouse.h"
#include "maze.h"

void move_forward(int8_t x, int8_t y, uint8_t heading)
{
  /*Physically move the mouse forward*/
  control_forward();

  /*figure out where we need to move the mouse on the map*/
  switch(heading)
  {
    case NORTH:
      y--;
      break;
    case EAST:
      x++;
      break;
    case SOUTH:
      y++;
      break;
    case WEST:
      x--;
      break;  
  }

  /*Set the mouse new position on the map*/
  mouse_set_x(x);
  mouse_set_y(y);
}