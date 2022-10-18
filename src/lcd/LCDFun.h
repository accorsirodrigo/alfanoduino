/*
   Centraliza as funcs referentes ao display;
*/

// void printDisplay(int x, int y, String txt, int size, LiquidCrystal_I2C &lcd) {
//   while (txt.length() < size) {
//     txt.concat(" ");
//   }
//   if (txt.length() > size)
//     txt = txt.substring(0, size);

//   lcd.setCursor(x, y);
//   lcd.print(txt);
// }


// void welcomeScreen(LiquidCrystal_I2C &lcd) {
//   printDisplay(0, 0, "###################", 20, lcd);
//   printDisplay(6, 1, "DuinoFano", 20, lcd);
//   printDisplay(4, 2, "Version 0.5.1", 20, lcd);
//   printDisplay(6, 3, "Kart GPS", 20, lcd);
// }

// void initLcdLayout(LiquidCrystal_I2C &lcd) {
//   lcd.noBacklight();
//   lcd.clear();
//   delay(500);
//   String lap = "LAP:";
//   String bst = "BST:";
//   printDisplay(0, 2, lap, lap.length(), lcd);
//   printDisplay(0, 3, bst, bst.length(), lcd);
//   lcd.backlight();
// }