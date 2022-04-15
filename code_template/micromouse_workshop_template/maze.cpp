#include "maze.h"

/*Virtual mouse object*/
mouse_t mouse = {.x = 0, .y = 0, .heading = NORTH};

/*Maze cells array*/
cell_t maze[MAZE_WIDTH][MAZE_HEIGHT];

int8_t maze_set_wall(uint8_t x, uint8_t y, uint8_t wall)
{
  if(CHECK_BOUNDARIES(x, y)) return -1;
  
  maze[x][y].walls |= wall;

  switch(wall)
  {
    case NORTH:
      maze[x][y-1].walls |= SOUTH;
      break;
    case EAST:
      maze[x+1][y].walls |= WEST;
      break;
    case SOUTH: 
      maze[x][y+1].walls |= NORTH;
      break;
    case WEST:
      maze[x-1][y].walls |= EAST;
      break; 
  }
}

int8_t maze_get_walls(uint8_t x, uint8_t y)
{
  if(CHECK_BOUNDARIES(x, y)) return -1;
   
  return maze[x][y].walls;
}

int8_t maze_set_value(uint8_t x, uint8_t y, uint8_t value)
{
  if(CHECK_BOUNDARIES(x, y)) return -1;
  
  maze[x][y].value = value;
}

int8_t maze_get_value(uint8_t x, uint8_t y)
{
  if(CHECK_BOUNDARIES(x, y)) return -1;

   return maze[x][y].value;
}

cell_t *maze_get_cell(uint8_t x, uint8_t y)
{
    if(CHECK_BOUNDARIES(x, y)) return NULL;
    
    return &maze[x][y];
}

void maze_init(uint8_t target_x, uint8_t target_y)
{
  if(CHECK_BOUNDARIES(target_x, target_y)) return;
  
  for(uint8_t y = 0; y < MAZE_HEIGHT; y++)
  {
    for(uint8_t x = 0; x < MAZE_WIDTH; x++)
    {
      maze[x][y].value = abs(target_x - x) + abs(target_y - y);
      maze[x][y].pos = X_POS(x) | Y_POS(y);  

      if(x == 0)                 maze[x][y].walls |= WEST;
      if(x == (MAZE_WIDTH - 1))  maze[x][y].walls |= EAST;
      if(y == 0)                 maze[x][y].walls |= NORTH;
      if(y == (MAZE_HEIGHT - 1)) maze[x][y].walls |= SOUTH;
    }
  }
}

/*Print routine for VT100 terminals. Recommended terminal is putty*/
void maze_print(void)
{
  /*Clear previous maze*/
  Serial.print("\x1B[2J");
  
  for(uint8_t y = 0; y < MAZE_HEIGHT; y++)
  {
    for(uint8_t x = 0; x < MAZE_WIDTH; x++)
    {
      uint8_t cy = 4*x + 1;
      uint8_t cx = 2*y + 1;

      /*Print cell value*/
      Serial.print("\x1B[");
      Serial.print(cx+1);
      Serial.print(";");
      Serial.print(cy+2);
      Serial.print("H");
      Serial.print(maze[x][y].value, DEC);

      /*Print north wall if present*/
      if(maze[x][y].walls & NORTH)
      {
        Serial.print("\x1B[");
        Serial.print(cx);
        Serial.print(";");
        Serial.print(cy);
        Serial.print("H");
        Serial.print("+---+");
      }
      
      /*Print east wall if present*/
      if(maze[x][y].walls & EAST)
      {
        Serial.print("\x1B[");
        Serial.print(cx+1);
        Serial.print(";");
        Serial.print(cy+4);
        Serial.print("H");
        Serial.print("|");
      }

      /*Print south wall if present*/
      if(maze[x][y].walls & SOUTH)
      {
        Serial.print("\x1B[");
        Serial.print(cx+2);
        Serial.print(";");
        Serial.print(cy);
        Serial.print("H");
        Serial.print("+---+");
      }

      /*Print west wall if present*/
      if(maze[x][y].walls & WEST)
      {
        Serial.print("\x1B[");
        Serial.print(cx+1);
        Serial.print(";");
        Serial.print(cy);
        Serial.print("H");
        Serial.print("|");
      }
    }
  }

  /*Print mouse's position and heading*/
  uint8_t mx = 2*mouse.y + 1;
  uint8_t my = 4*mouse.x + 1;

  Serial.print("\x1B[");
  Serial.print(mx+1);
  Serial.print(";");
  Serial.print(my+2);
  Serial.print("H");

  switch(mouse.heading)
  {
    case NORTH:
      Serial.print("^");
      break;
    case EAST:
      Serial.print(">");
      break;
    case SOUTH:
      Serial.print("V");
      break;
    case WEST:
      Serial.print("<");
      break;
  }
}

/*FlOOD FILL CODE GOES HERE***************************************************/

/*FlOOD FILL ENDS HERE********************************************************/

void mouse_set_x(int8_t x)
{
  if(x > (MAZE_WIDTH - 1)) { x = MAZE_WIDTH - 1; }
  if(x < 0) { x = 0; }
  
  mouse.x = x;
}

void mouse_set_y(int8_t y)
{
  if(y > (MAZE_HEIGHT - 1)) { y = MAZE_HEIGHT - 1; }
  if(y < 0) { y = 0; }
  
  mouse.y = y;
}

int8_t mouse_get_x(void)
{
  return mouse.x;
}

int8_t mouse_get_y(void)
{
  return mouse.y;
}

void mouse_set_heading(uint8_t heading)
{
  mouse.heading = heading;
}

uint8_t mouse_get_heading(void)
{
   return mouse.heading;
}
