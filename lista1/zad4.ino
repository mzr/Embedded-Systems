#define I0 A0

const int beepPin = 4;
const int hallPin = I0; 
const int diodPin= 3; 
const int buttonPin = 2;
int sensorValue = 0; // value read from the Linear pot

int frequency = 440;

int randomValue;

int diff;

void setup() {
  Serial.begin(9600);
  pinMode(diodPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  randomSeed(analogRead(0));
  randomValue = random(0,510);
  Serial.println(randomValue);

}
int state = 0;
unsigned long prev_time = 0;
int ratio = 2;
int sensitivity = 20;
int win = 0;

void loop() {
  sensorValue = analogRead(hallPin);

  diff = abs(randomValue - sensorValue);
  if( diff <= sensitivity )
  {
    digitalWrite(diodPin, HIGH);
    tone(beepPin, frequency);
    win = 1;
  }
  else
  {
    win = 0;
    digitalWrite(diodPin, LOW);
  }

  if(!win){
  unsigned long curr_time = millis();
  if((curr_time - prev_time) >= ratio * diff ) {
    if(state) {
      noTone(beepPin);
      state = 0;
    }
    else {
      tone(beepPin, frequency);
      state = 1;
    }
    prev_time = curr_time;
  }
}
  if(digitalRead(buttonPin) == HIGH) {
    randomValue = random(0, 510);
    digitalWrite(diodPin, LOW);
    Serial.println("halo");
  }
  Serial.println(sensorValue);


  

}