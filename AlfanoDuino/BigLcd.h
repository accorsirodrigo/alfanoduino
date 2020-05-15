void loadChars(LiquidCrystal_I2C &lcd)
{

    byte LT[8] = {
        B00111,
        B01111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
    byte UB[8] = {
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000};
    byte RT[8] = {
        B11100,
        B11110,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
    byte LL[8] = {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B01111,
        B00111};
    byte LB[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111,
        B11111};
    byte LR[8] = {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11110,
        B11100};
    byte MB[8] = {
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111};
    byte block[8] = {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};

    lcd.createChar(0, LT);
    lcd.createChar(1, UB);
    lcd.createChar(2, RT);
    lcd.createChar(3, LL);
    lcd.createChar(4, LB);
    lcd.createChar(5, LR);
    lcd.createChar(6, MB);
    lcd.createChar(7, block);
}

void custom0(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(1);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
}
void custom1(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write(1);
    lcd.write(2);
    lcd.print(" ");
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(7);
    lcd.write(4);
}
void custom2(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write(6);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(4);
}
void custom3(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write(6);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(4);
    lcd.write(5);
}
void custom4(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write(3);
    lcd.write(4);
    lcd.write(7);
    lcd.setCursor(x, 1);
    lcd.print(" ");
    lcd.print(" ");
    lcd.write(7);
}
void custom5(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write(3);
    lcd.write(6);
    lcd.write(6);
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(4);
    lcd.write(5);
}
void custom6(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(6);
    lcd.write(6);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
}
void custom7(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.print(" ");
    lcd.print(" ");
    lcd.write(7);
}
void custom8(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
}
void custom9(LiquidCrystal_I2C &lcd, int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.print(" ");
    lcd.print(" ");
    lcd.write(7);
}
void printDigits(LiquidCrystal_I2C &lcd, int digits, int x)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    switch (digits)
    {
    case 0:
        custom0(lcd, x);
        break;
    case 1:
        custom1(lcd, x);
        break;
    case 2:
        custom2(lcd, x);
        break;
    case 3:
        custom3(lcd, x);
        break;
    case 4:
        custom4(lcd, x);
        break;
    case 5:
        custom5(lcd, x);
        break;
    case 6:
        custom6(lcd, x);
        break;
    case 7:
        custom7(lcd, x);
        break;
    case 8:
        custom8(lcd, x);
        break;
    case 9:
        custom9(lcd, x);
        break;
    }
}

void printNumber(LiquidCrystal_I2C &lcd, int val)
{
    int col = 0;
    printDigits(lcd, val / 100, col);
    printDigits(lcd, (val % 100) / 10, col + 4);
    printDigits(lcd, val % 10, col + 8);
}

int version(void)
{
    return 1;
}
