#define pmin 2
#define pmax 3
#define foto A5
#define led 10

int wartosc;
int pwm;
int lewy, prawy;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pmin, INPUT_PULLUP);
  pinMode(pmax, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  lewy=0;
  prawy=1023;
}

void loop() {
  // put your main code here, to run repeatedly:
  wartosc = analogRead(foto);
  //Serial.print("!");
  //Serial.println(wartosc);
  pisz(wartosc, lewy, prawy);
  delay(100);

  if (digitalRead(pmin) == LOW)
  {
    lewy=wartosc; //dla tej wartości nie świeci
  }

  if (digitalRead(pmax) == LOW) //jak latarką z komórki z odl. 1 cm centralnie nad, to pwm będzie 60 w ten sposób
  {
    prawy=wartosc;
  }
}

void pisz ( int wartosc, int lewy, int prawy)
{
  int cowyjdzie;
  int mi=min(lewy, prawy);
  int ma=max(lewy, prawy);
  wartosc=constrain(wartosc, mi, ma);
  pwm = map(wartosc, lewy, prawy, 0, 255); //przetwarzamy procenty 5'ciu V na %'ty pwm
  Serial.println(pwm);
  analogWrite(led,pwm);
}
