/*
 * BitFont.h - Bit Font library for Arduino - Version 0.1
 *
 * Derived from ...
 *   Original library        (0.1)   by Tom Igoe and others
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Drives 4 row, character type Liquid Crystal Displays with 4x4 fonts of special symbols
 *
 */

// ensure this library description is only included once
#ifndef BigFont_h
#define BigFont_h
#include <LiquidCrystal.h>

// library interface description
class BigFont {
  public:
    // constructor:
    BigFont();

    // load special characters
    void loadchars(LiquidCrystal& lcd);  

    // print char method
    void printblankchar(LiquidCrystal& lcd, byte col, byte row);
    void printbigchar(LiquidCrystal& lcd, byte digit, byte col, byte row, byte symbol); 

    int version(void);

  private:
   // Define the large fonts, borrowed from GreenHerron RT-21 pictures
   // Define here globally for Class so not define on each call to print character
   byte bignums[10][4][4] = 
   {
      { // 0
	{  1,   2,   2,   3},
	{255, 254, 254, 255},
	{255, 254, 254, 255},
	{  4,   5,   5,   6}
      },
      { // 1
	{254,   1, 255, 254},
	{254, 254, 255, 254},
	{254, 254, 255, 254},
	{254,   5, 255,   5}
      },
      { // 2
	{  1,   2,   2,   3},
	{254, 254,   5,   6},
	{  1,   2, 254, 254},
	{255,   5,   5,   5}
      },
      { // 3
	{  1,   2,   2,   3},
	{254, 254,   5,   6},
	{254, 254,   2,   3},
	{  4,   5,   5,   6}
      },      
      { // 4
	{255, 254, 254, 255},
	{255, 254, 254, 255},
	{  4,   2,   2, 255},
	{254, 254, 254, 255}
      },
      { // 5
	{255,   2,   2,   2},
	{  4,   5,   5,   3},
	{254, 254, 254, 255},
	{  4,   5,   5,   6}
      },
      { // 6
	{  1,   2,   2, 254},
	{255,   5,   5,   3},
	{255, 254, 254, 255},
	{  4,   5,   5,   6}
      },
      { // 7
	{  4,   2,   2, 255},
	{254, 254,   1,   6},
	{254, 254, 255, 254},
	{254, 254, 255, 254}
      },
      { // 8
	{  1,   2,   2,   3},
	{  4,   5,   5,   6},
	{  1,   2,   2,   3},
	{  4,   5,   5,   6}
      },
      { // 9
	{  1,   2,   2,   3},
	{255, 254, 254, 255},
	{  4,   2,   6, 255},
	{254,   5,   5,   6}
      }
   }; // bignums[]
}; // Class BigFont
#endif

