#define Xaxis 0 //analog
#define Yaxis 1 //analog
#define Ndiod 2
#define Ediod 3
#define Sdiod 4
#define Wdiod 5
#define key 7

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Serial.print("\n");

  pinMode(Ndiod, OUTPUT);
  pinMode(Ediod, OUTPUT);
  pinMode(Sdiod, OUTPUT);
  pinMode(Wdiod, OUTPUT);
  pinMode(key, INPUT_PULLUP);

  

  diodsOff();

  randomSeed(analogRead(5));

  manual();
  Serial.write("Rozpoczeto nowa gre. Wprowadz czas rozgrywki w sekundach.\n");
}

long gameTime=100;
  bool whatTime=true;
  bool game=false;
  long score=0;
  int r;
  bool go=false;
  long scoreTime=0;
  bool noCheat=false;
  bool ifnew = false;
long startTime;

void loop() {
  // put your main code here, to run repeatedly:

  

  int Xval, Yval;

  if (Serial.available()>0)
  {
    String napis = Serial.readString();
    if (napis=="nowa")
    {
      nowa(score);
    }
    else if (napis=="help")
    {
      manual();
    }
    else if(whatTime) 
    {
      gameTime=napis.toInt();
      Serial.print("Gra sie rozpoczela\n");
      ifnew=false;
      Serial.print(gameTime);
      game=true;
      whatTime=false;
      go=true;
      r=random(0,4);
      diod(r);
      scoreTime=millis();
      startTime=millis();
      score=0;
      noCheat=false;
    }
    
    
  }

  if(game && millis() - startTime > 1000*gameTime) {
    nowa(score); 
  }

  if (!digitalRead(key)) { nowa(score); }

  
  Xval = analogRead(Xaxis);

  delay(10); //ponoć wolno czyta i inaczej się dostaje to samo; było 100

  Yval = analogRead(Yaxis);

  //Serial.println(Xval);
  //Serial.println(Yval);
  //Serial.println(noCheat);
  //Serial.println(r);

  if (abs(512-Xval) < 20 && abs(512-Yval) < 20) noCheat = true;

  if(game && correct(Xval,Yval,r) && noCheat) {
    long deltaT = millis() - scoreTime;
    long scoreNow = max(0, (1000-deltaT)/100);
    score+=scoreNow;
    Serial.print("Zdobyles: ");
      Serial.print(scoreNow);
      Serial.print(" punktow\n");
    r=random(0,4);
    diod(r);
    scoreTime=millis();
    noCheat=false;
  }
}

void manual(){
  Serial.write("Gra polega na przesunieciu joysticka w kierunku zapalonej diody\n \
                diody zapalaja sie losowo. Przed przesunieciem w kierunku diody\n \
                joystick musi znajdowac sie w pozycji zero. Za prawidlowe przesuniecie\n \
                joysticka gracz dostaje max(0, (1000-t)/100) punktow,\n \
                gdzie t jest czasem od zapalenia sie diody do przesuniecia joysticka\n \
                liczonym w milisekundach\n \
                polecenia:\n nowa - nowa gra, \n help - wyswietlenie tej instrukcji\n nacisniecie joysticka - nowa gra\n");

  //pozycja zero to jest ten "anti-cheat"
}

void diod(int r){
  
  diodsOff();

  int stahp = random(100,1000);
  delay(stahp);

  diodOn(r);
}

void diodsOff() {
  digitalWrite(Ndiod, LOW);
  digitalWrite(Ediod, LOW);
  digitalWrite(Sdiod, LOW);
  digitalWrite(Wdiod, LOW);
}


void diodOn(int r) {
  switch(r) {
    case 0:
      digitalWrite(Ndiod, HIGH);
      break;
    case 1:
      digitalWrite(Ediod, HIGH);
      break;
    case 2:
      digitalWrite(Sdiod, HIGH);
      break;
    case 3:
      digitalWrite(Wdiod, HIGH);
      break;
  }
}


bool correct(int x, int y, int r) {
  return (  (y>812 && abs(x-512)<50 && r==0)
         || (y<212 && abs(x-512)<50 && r==2)
         || (x>800 && abs(y-512)<50 && r==1)
         || (x<212 && abs(y-512)<50 && r==3) );
}



void nowa(long score) {
  if (ifnew) return;
  diodsOff();
  Serial.print("\nTwoj wynik: ");
      Serial.print(score);
      Serial.print(" punktow\n");
      Serial.print("Rozpoczeto nowa gre. Wprowadz czas rozgrywki w sekundach.\n");
      game=false;
      whatTime=true;
      ifnew =true;
}





