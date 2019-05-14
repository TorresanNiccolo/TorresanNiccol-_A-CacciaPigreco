#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int btn_Start = 2;
int btn_1 = 5;
int btn_2 = 7;
int btn_3 = 9;
int btn_4 = 11;
int btn_5 = 13;

byte Cuore[8] = {B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000};
byte PiGreco[8] = {B00000, B10110, B01001, B01010, B01010, B01010, B01010, B0000};

void setup() 
{
  lcd.createChar(0, Cuore);
  lcd.createChar(1, PiGreco);
  lcd.init();
  lcd.backlight();
  
  pinMode(btn_Start, INPUT);
  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
  pinMode(btn_3, INPUT);
  pinMode(btn_4, INPUT);
  pinMode(btn_5, INPUT);
}


void loop() 
{
  inizio();
  if (digitalRead(btn_Start) == HIGH)
  {
    int num = random(1, 8);
    if (num == 6 || num == 7)
    {
      simboli(num, random(1, 6));
    }
    else 
    {
      piGreco(num);
    }
  }
}

void piGreco(int btn)
{
  int posizione = (btn * 3) - 1;
  delay(2000);
  lcd.setCursor(posizione, 1);
  lcd.print("P");

  int tempoPassato = 0;
  
  while(digitalRead(btn) == HIGH && tempoPassato < tempo)
  {
    tempoPassato++;
    delay(1);

    if (btn != btn_1 && digitalRead(btn_1) == HIGH || btn != btn_2 && digitalRead(btn_2) == HIGH || btn != btn_3 && digitalRead(btn_3) == HIGH || btn != btn_4 && digitalRead(btn_4) == HIGH || btn != btn_5 && digitalRead(btn_5) == HIGH)
    {
      nVite--;
      nMatch++;
      break;
    }
  }
  
  lcd.setCursor(6, 0);
  lcd.print(nVite);
  lcd.setCursor(15, 0);
  lcd.print(nMatch);
}

void simboli(int n, int btn)
{
   int posizione = (btn * 3) - 1;
  if (n == 6)
  {
    lcd.setCursor(posizione, 1);
    lcd.write(byte(0));
  }
  else if (n == 7)
  {
    lcd.setCursor(posizione, 1);
    lcd.print("X");
  }
}

void inizio()
{
  int nVite = 5;
  int nMatch = 0;
  int tempo = 4000;

  while (digitalRead(btn_Start) == LOW)
  {
    lcd.setCursor(4, 0);
    lcd.print("PREMI PER");
    lcd.setCursor(4, 1);
    lcd.print("INIZIARE");
  }
  
  lcd.setCursor(0, 0);
  lcd.print("VITE:" + (String)nVite);
  lcd.setCursor(9, 0);
  lcd.print("MATCH:" + (String)nMatch);
}
