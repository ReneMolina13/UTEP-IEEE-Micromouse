#include "micromouse.h"
#include "maze.h"

uint8_t find_best_neighbor(int x, int y)
{
  /*Neighbor offsets for all orientations*/
  int8_t neighbor_offset[4][2] = 
  {
    {0, -1}, 
    {1,  0},  
    {0,  1},
    {-1, 0},
  };
    
  /*Get current cell*/
  cell_t *current = maze_get_cell(x, y);
  cell_t *neighbor_cell;

  /*Assume lowest value is the highest distance*/
  uint8_t lowest_value = 255;
  /*Assume best neighbor is to the north*/
  uint8_t best_neighbor = NORTH; 
  for(int i = 0; i < 4; i++)
  {
    /*If the neighbor is open...*/
    if((current->walls & (1 << i)) == 0)
    {
      /*Get neighbor coordinates*/
      int8_t nx = x + neighbor_offset[i][0];
      int8_t ny = y + neighbor_offset[i][1];

      /*Get neighbor cell value*/
      neighbor_cell = maze_get_cell(nx, ny);
      if(neighbor_cell->value < lowest_value)
      {
        /*If this this lower than the previous cell value, then set it as
         * the new minimum
         */
        lowest_value = neighbor_cell->value;
        best_neighbor = (1 << i);
      }
    }
  }

  return best_neighbor;
}