#define pmin 2
#define pmax 4
#define foto A5
#define buzz 10

#define diodarec 5
#define diodafull 6
#define diodaodtw 7 
#define nagrywaj 12
#define odtwarzaj 13

#define MAX 600


int wartosc;
int pwm;
int lewy, prawy;

short tab[MAX];  //nie można użyć PROGMEM żeby się więcej zmieściło, bo musiałoby być const

int pocznagr = 0;
int koncnagr = 0;
int ostnagr;
int ostodtw;
int drgania = 100;
long kiedypisal; //bez tego się przekręca i źle
long coile = 20;

bool czynagrywa = false;
bool czyodtwarza = false;
bool wcisnietynagr = false;
bool wcisnietyodtw = false;

void full()
{
  digitalWrite(diodafull,1);
  digitalWrite(diodarec,0);
  delay(300);
  digitalWrite(diodafull,0);
  czynagrywa = false;
}

void pisz ( int wartosc, int lewy, int prawy)
{
  int cowyjdzie;
  int mi=min(lewy, prawy);
  int ma=max(lewy, prawy);
  wartosc=constrain(wartosc, mi, ma);
  pwm = map(wartosc, lewy, prawy, 50, 500); //przetwarzamy miejsce zakresu na zakres jakichś spoko częstotl 50-500Hz
  //Serial.println(pwm);
  //noTone(buzz); //to jest potrzebne tylko na różnych pinach, lub na końcu a na jednym znacznie pogarsza dźwięk
  if (czynagrywa) {
    if (koncnagr >= MAX) full();
    else {
      tab[koncnagr] = pwm;
      ++koncnagr;
    }
  }
  tone(buzz,pwm);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pmin, INPUT_PULLUP);
  pinMode(pmax, INPUT_PULLUP);
  pinMode(nagrywaj, INPUT_PULLUP);
  pinMode(odtwarzaj, INPUT_PULLUP);

  pinMode(buzz, OUTPUT);
  pinMode(diodarec, OUTPUT);
  pinMode(diodafull, OUTPUT);
  pinMode(diodaodtw, OUTPUT);
  digitalWrite(buzz, LOW);
  digitalWrite(diodarec, LOW);
  digitalWrite(diodafull, LOW);
  digitalWrite(diodaodtw, LOW);
  lewy=0;
  prawy=1023;
}

void loop() {
  // put your main code here, to run repeatedly:
  wartosc = analogRead(foto);
  
  if (millis() - kiedypisal > coile) {
    if (!czyodtwarza) pisz(wartosc, lewy, prawy);
    else if (!czynagrywa) { //warunek niepotrzebny
      if (pocznagr >= koncnagr) { //na pocz. bo mogło by być puste nagranie
        czyodtwarza = false;
        digitalWrite(diodaodtw,0);
        
      }
      else {
        tone(buzz,tab[pocznagr]);
        ++pocznagr;
      }
      
    }
    kiedypisal = millis();
  }
  

  if (!czyodtwarza && digitalRead(pmin) == LOW) //dla przycisków min, max nie patrzymy na drganie styków bo naciśnięcie kilka razy nic nie zmienia
  {
    lewy=wartosc; //dla tej wartości nie świeci
  }

  if (!czyodtwarza && digitalRead(pmax) == LOW) //jak latarką z komórki z odl. 1 cm centralnie nad, to pwm będzie 60 w ten sposób
  {
    prawy=wartosc;
  }

  if (!wcisnietynagr && !czyodtwarza && digitalRead(nagrywaj) == LOW && millis() - ostnagr > drgania) //żeby zacząć nagrywać trzeba skończyć odtwarzać i odwrotnie, bez syfu
  {
    //Serial.println("rec");
    wcisnietynagr = true;
    ostnagr=millis();
    if (czynagrywa) {
      czynagrywa = false; 
      digitalWrite(diodarec,0);
    }
    else { 
      digitalWrite(diodarec,1);
      czynagrywa = true;
      koncnagr = 0;
      kiedypisal = millis() - coile;
    }
  }

  if (!wcisnietyodtw && !czynagrywa && digitalRead(odtwarzaj) == LOW && millis() - ostodtw > drgania)  //żeby zacząć nagrywać trzeba skończyć odtwarzać i odwrotnie, bez syfu
  {
    Serial.println("odtw");
    wcisnietyodtw = true;
    ostodtw = millis();
    if (czyodtwarza) {
      czyodtwarza=false;
      digitalWrite(diodaodtw,0);
    }
    else {
      digitalWrite(diodaodtw,1);
      pocznagr = 0;
      czyodtwarza = true;
      kiedypisal = millis() - coile;
    }
  }

  if(wcisnietynagr && !czyodtwarza && digitalRead(nagrywaj) == HIGH && millis() - ostnagr > drgania) wcisnietynagr = false;
  if (wcisnietyodtw && !czynagrywa && digitalRead(odtwarzaj) == HIGH && millis() - ostodtw > drgania) wcisnietyodtw = false;
}


