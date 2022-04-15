#include "micromouse.h"
#include "maze.h"

const int IR_FRONT_WALL_THRESHOLD = 700;
const int IR_RIGHT_WALL_THRESHOLD = 700;
const int IR_LEFT_WALL_THRESHOLD = 700;

void scan_walls(int x, int y, uint8_t heading)
{
  /*Measure all IR sensors*/
  int ir0 = ir_0_read(150);
  int ir1 = ir_1_read(150);
  int ir2 = ir_2_read(150);
  int ir3 = ir_3_read(150);

  /*Threshold for front sensors*/
  int ir_front = (ir0 + ir3)/2;
  if(ir_front > IR_FRONT_WALL_THRESHOLD)
  {
    /*There is a wall at the front*/
    /*Just set the wall to the current heading of the mouse*/
    maze_set_wall(x, y, heading);
  }

  /*Threshold for right sensor*/
  if(ir1 > IR_RIGHT_WALL_THRESHOLD)
  {
    /*There is a wall on our left*/
    /*Bit shift heading for correct wall positioning*/
    uint8_t wall = heading << 1;     
    /*If bigger than 16, then wrap around back to 1*/
    if(wall > 8)
    {
      wall /= 16;
    }

    maze_set_wall(x, y, wall);
  }

  /*Threshold for left sensor*/
  if(ir2 > IR_LEFT_WALL_THRESHOLD)
  {
    /*There is a wall on our right*/
    /*Bit shift heading for correct wall positioning*/
    uint8_t wall = heading << 3;     
    /*If bigger than 16, then wrap around back to 1*/
    if(wall > 8)
    {
      wall /= 16;
    }

    maze_set_wall(x, y, wall);
  }
}