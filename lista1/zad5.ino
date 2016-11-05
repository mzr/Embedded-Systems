int ledPin = 13;
int btnPin = 2;

int current;
int previous = 0;

int i=0;
int j=0;
int i2=0;
int j2=0;

int ddelay = 1000;

int t[100][2];
int t_length = 100;

int isOn = 0;
int rls = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
//  pinMode(btnPin,INPUT);
  digitalWrite(btnPin,HIGH);
}
void loop() {
  current = digitalRead(btnPin);

  if( previous == 0 && current == 1) //pressed
  {
    Serial.print("press-");
    t[i][j] = millis();
    j++;
  }

  if( previous == 1 && current == 0) //released
  {
    Serial.print("release-");
    t[i][j] = millis();
    j = 0;
    i = (i+1) % t_length;
    
    Serial.print(t[i-1][1] - t[i-1][0]);
    Serial.print("    ");
  }

  if( millis() - t[i2][j2] >= ddelay && i2 < i && isOn == 0 ) //wlacz diode
  {
   isOn = 1;
   digitalWrite(ledPin,HIGH);
   j2++; 
  }

  if( millis() - t[i2][j2] >= ddelay && i2 < i && isOn == 1) //wylacz diode
  {
    isOn = 0;
    digitalWrite(ledPin,LOW);
    j2 = 0;
    i2 = (i2+1) % t_length;
  }

  
  previous = current;
}



