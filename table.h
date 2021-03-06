/*
This file is used for everything related to maps/tables including their definition, functions etc
*/
#ifndef TABLE_H
#define TABLE_H
#include <Arduino.h>

/*
The 2D table can contain either 8-bit (byte) or 16-bit (short) values
The valueSize variable should be set to either 8 or 16 to indicate this BEFORE the table is used
*/
struct table2D {
  byte valueSize; 
  byte xSize;
  
  byte *values;
  byte *axisX;
  
  short *values16;
  short *axisX16;
  
  //Store the last X and Y coordinates in the table. This is used to make the next check faster
  short lastXMax, lastXMin;
};

void table2D_setSize(struct table2D targetTable, byte newSize);

struct table3D {
  
  //All tables must be the same size for simplicity
  
  byte xSize;
  byte ySize;
  
  byte **values;
  short *axisX;
  short *axisY;
  
  //Store the last X and Y coordinates in the table. This is used to make the next check faster
  byte lastXMax, lastXMin;
  byte lastYMax, lastYMin;
};

void table3D_setSize(struct table3D *targetTable, byte newSize);

/*
3D Tables have an origin (0,0) in the top left hand corner. Vertical axis is expressed first.
Eg: 2x2 table
-----
|2 7|
|1 4|
-----

(0,1) = 7
(0,0) = 2
(1,0) = 1

*/
short get3DTableValue(struct table3D *fromTable, short, short);
short table2D_getValue(struct table2D *fromTable, short);

#endif // TABLE_H
