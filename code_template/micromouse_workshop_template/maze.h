#ifndef MAZE_H_
#define MAZE_H_

#include <stdint.h>
#include <stdlib.h>

#include <Arduino.h>

#define MAZE_WIDTH    8
#define MAZE_HEIGHT   8

#define X_POS(x)  (x & 0x0F)
#define Y_POS(y)  ((y << 4) & 0xF0)

#define GET_X_POS(x)  (x & 0x0F)
#define GET_Y_POS(y)  (y >> 4)

#define NORTH   (1 << 0)
#define EAST    (1 << 1)
#define SOUTH   (1 << 2)
#define WEST    (1 << 3)

#define CHECK_BOUNDARIES(x, y)    (x > (MAZE_WIDTH - 1)) ||   \
                                  (y > (MAZE_HEIGHT - 1))                              
typedef struct
{
  uint8_t value;
  uint8_t pos;
  uint8_t walls;
}cell_t;

typedef struct
{
  int8_t x;
  int8_t y;
  uint8_t heading;
}mouse_t;

int8_t maze_set_wall(uint8_t x, uint8_t y, uint8_t wall);
int8_t maze_get_walls(uint8_t x, uint8_t y);
int8_t maze_set_value(uint8_t x, uint8_t y, uint8_t value);
int8_t maze_get_value(uint8_t x, uint8_t y);
cell_t *maze_get_cell(uint8_t x, uint8_t y);

void maze_init(uint8_t target_x, uint8_t target_y);
void maze_print(void);

void mouse_set_heading(uint8_t heading);
uint8_t mouse_get_heading(void); 
void mouse_set_x(int8_t x);
void mouse_set_y(int8_t y);
int8_t mouse_get_x(void);
int8_t mouse_get_y(void);

#endif
