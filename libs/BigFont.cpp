/*
 * BigFont.cpp - Big Font library for Arduino - Version 0.1
 *
 * Derived from Stepper.cpp
 *   Original library        (0.1)   by Tom Igoe et al...
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
 */

#include "BigFont.h"
#include <LiquidCrystal.h>

/*
 * Big Font constructor, doesn't do anything
 */
BigFont::BigFont()
{
}

/*
 * Load the special characters in LCD driver chip
 * Called once on configuring custom characters
 */
void BigFont::loadchars(LiquidCrystal& lcd) 
{
  // Define the custom characters
  // The order is 1,2,3 for curved top, 4,5,6 for curved bottom
  // 0 is allegedly not usable, 7 is the degree symbol
  byte custchar[8][8] = 
  {
    { // 0
	B11111,
	B11111,
	B11111,
	B11111,
	B00000,
	B00000,
	B00000,
	B00000
      }, 
      { // 1
	B00000,
	B00000,
	B00000,
	B00001,
	B00011,
	B00111,
	B01111,
	B11111
      },
      { // 2
	B11111,
	B11111,
	B11111,
	B11111,
	B00000,
	B00000,
	B00000,
	B00000   
      }, 
      { // 3
	B00000,
	B00000,
	B00000,
	B10000,
	B11000,
	B11100,
	B11110,
	B11111
      }, 
      { // 4
	B11111,
	B01111,
	B00111,
	B00011,
	B00001,
	B00000,
	B00000,
	B00000
      }, 
      { // 5
	B00000,
	B00000,
	B00000,
	B00000,
	B11111,
	B11111,
	B11111,
	B11111
      }, 
      { // 6
	B11111,
	B11110,
	B11100,
	B11000,
	B10000,
	B00000,
	B00000,
	B00000
      }, 
      { // 7
	B00000,
	B00000,
	B01110,
	B10001,
	B10001,
	B10001,
	B01110,
	B00000
      }
  }; // custchar[]

  // load custom characters into display controller memory
  lcd.createChar(0, custchar[0]);
  lcd.createChar(1, custchar[1]);
  lcd.createChar(2, custchar[2]);
  lcd.createChar(3, custchar[3]);
  lcd.createChar(4, custchar[4]);
  lcd.createChar(5, custchar[5]);
  lcd.createChar(6, custchar[6]);
  lcd.createChar(7, custchar[7]);  
}

// print blank character
void BigFont::printblankchar(LiquidCrystal& lcd, byte col, byte row)
{
   for(int i = 0; i < 4; i++) // for each row
   {
      lcd.setCursor(col, row + i);
      for(int j = 0; j < 4; j++) // for each column
      {
        lcd.write(254);  // blank char
      } // for(i...
   } // for(j...
} // printblankchar()

// digit 0-9; col, row in LCD character, symbol
void BigFont::printbigchar(LiquidCrystal& lcd, byte digit, byte col, byte row, byte symbol) 
{
  if (digit > 9 | digit < 0) return;
  // loop over the font and write to lcd
  for (int i = 0; i < 4; i++)    // for each row
  {
    lcd.setCursor(col, row + i); //set the row address
    for (int j = 0; j < 4; j++)  // for each column of font
    {
      lcd.write(this->bignums[digit][i][j]); // increments the col address also
    }
    lcd.write(254); // write blank to 5th column
  }
  // write the deg symbol at the top of the 5th column
  if (symbol == 1) 
  {
    lcd.setCursor(col + 4, row + 0);
    lcd.write(7); // deg symbol
  }
}

// version() returns the version of the library:
int BigFont::version(void)
{
  return 1;
}
