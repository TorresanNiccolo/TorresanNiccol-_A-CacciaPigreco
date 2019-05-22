
//Niccolò Torresan 3BI 
//Caccia al Pi-Greco

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//DICHIARO LE VARIABILI

int btn_Start = 2;
int btn_1     = 7;
int btn_2     = 8;
int btn_3     = 9;
int btn_4     = 10;
int btn_5     = 11;

int nVite ;
int nPunti;
int tempo ;
int tempoPassato;

bool errore;

void setup()
{
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
  nVite = 5;
  while (nVite > 0)
  {
    delay(1000);
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

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("HAI FINITO");
  lcd.setCursor(4, 1);
  lcd.print("LE VITE");
  delay(3000);
  inizio();
}

void piGreco(int btn)
{
  bool err = bonusMalus(btn, "P");
  if (err == false)
  {
    tempo -= 100;
    nPunti++;
  }
  else
  {
    nVite--;
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
    bool err = bonusMalus(btn, "B");
    if (err == false)
    {
      nVite++;
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
  else if (n == 7)
  {
    bool err = bonusMalus(btn, "X");
    if (err == false)
    {
      nVite--;
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
}

void inizio()
{
  lcd.clear();
  nVite = 5;
  nPunti = 0;
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
  lcd.print("PUNTI:" + (String)nPunti);
}

bool bonusMalus(int btn, char s)
{
  delay(2000);
  tempoPassato = 0;
  int posizione = (btn * 3) - 1;
  lcd.setCursor(posizione, 1);
  lcd.write(s);
  errore = false;

  while (tempoPassato < tempo && !errore)
  {
    if (digitalRead(btn + 6) == HIGH)
    {
      break;
    }
    else
    {
      for (int a = 7; a < 12; a++)
      {
        if (a != (btn + 6) && digitalRead(a) == HIGH)
        {
          return true;
          break;
        }
      }
    }
    tempoPassato++;
    delay(1);
  }
  if (tempo == tempoPassato)
  {
    return true;
  }
  else
  {
    return false;
  }
}
