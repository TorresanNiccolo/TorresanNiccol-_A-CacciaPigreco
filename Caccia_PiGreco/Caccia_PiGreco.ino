#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int btn_Start = 2;
int btn_1     = 5;
int btn_2     = 7;
int btn_3     = 8;
int btn_4     = 9;
int btn_5     = 10;

int nVite ;
int nPunti;
int tempo ;
int tempoPassato;

byte Cuore[8]   = {B00000, B01010, B11111, B11111, B11111, B01110, B00100, B00000};
byte PiGreco[8] = {B00000, B11111, B01010, B01010, B01010, B01010, B00000, B00000};

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
  
  inizio();
}


void loop()
{
  if (nVite > 0)
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
  else
  {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("HAI FINITO");
    lcd.setCursor(4, 1);
    lcd.print("LE VITE");
    inizio();
  }
}

void piGreco(int btn)
{
  delay(2000);
  tempoPassato = 0;
  int posizione = (btn * 3) - 1;
  btn += 7;
  lcd.setCursor(posizione, 1);
  lcd.write(byte(1));

  while (digitalRead(btn) == LOW)
  {
    tempoPassato++;
    delay(1);
    if ((btn != btn_1 && digitalRead(btn_1) == HIGH ) || (btn != btn_2 && digitalRead(btn_2) == HIGH) || (btn != btn_3 && digitalRead(btn_3) == HIGH) || (btn != btn_4 && digitalRead(btn_4) == HIGH) || (btn != btn_5 && digitalRead(btn_5) == HIGH) || tempoPassato > tempo)
    {
      nVite--;
      tempo -= 100;
      break;
    }
    else
    {
      nPunti++;
      break;
    }
  }

  for (int i = 0; i < 16; i++)
  {
    lcd.setCursor(i, 1);
    lcd.print(" ");
  }

  lcd.setCursor(5, 0);
  lcd.print(nVite);
  lcd.setCursor(14, 0);
  lcd.print(nPunti);
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
  lcd.clear();
  nVite = 5;
  nMatch = 0;
  tempo = 4000;
  tempoPassato = 0;

  while (digitalRead(btn_Start) == LOW)
  {
    lcd.setCursor(4, 0);
    lcd.print("PREMI PER");
    lcd.setCursor(4, 1);
    lcd.print("INIZIARE");
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VITE:" + (String)nVite);
  lcd.setCursor(8, 0);
  lcd.print("MATCH:" + (String)nMatch);
}
