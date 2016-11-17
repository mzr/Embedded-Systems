#define btnPin 2
#define diodPin 7
#define beepPin 9

int kropka = 300;

int tolerancja = 10;

int time_press;
int hold = 0;
int time_held;

int time_release;
int released = 0;
int time_unheld;

//#define pojemnosc 200

//char el[pojemnosc];
//int el_index = 0;
String el = String(""); 

//char znak[pojemnosc];
//int znak_index = 0;
String znak = String("");

void setup() {
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);
  
  pinMode(diodPin, OUTPUT);
//  digitalWrite(diodPin,HIGH);
  //tone(beepPin,540);
  
  
  
}

void loop() {
  int sensorVal = digitalRead(btnPin); //gdy puszczony to jest 1
  
  if(sensorVal == 0 && hold == 0) // on press
  {
   hold = 1;
   time_press = millis();
  // Serial.println("pressed");
   if(released == 1) {
     time_unheld = millis() - time_release;
      //Serial.println(time_unheld);
   
   
   if(time_unheld <= 2*kropka) //to znaczy ze to co bylo to byl el znaku
   {
    Serial.println("to element znaku");
   }
   if(time_unheld > 2*kropka && time_unheld <= 5*kropka ) // z tablicy el robimy litere
   {
     Serial.println("to literka");
     znak = String(znak + morse_to_letter(el));
     Serial.println(morse_to_letter(el));
     el = String("");
   }
   if(time_unheld > 5*kropka)
   {
     Serial.println("to slowo");
    znak = String(znak + " ");
    Serial.println(znak);
    znak = String(""); 
     
   }
   }
   released = 0;
  }
  
  if(sensorVal == 1 && hold == 1) //on release
  {
   hold = 0;
   time_held = millis() - time_press; 
//    Serial.println("released");
    //Serial.println(time_held);
    //Serial.println("seconds"); 
   released = 1;
   time_release = millis();
   
   
   if(time_held >= 3*kropka) //mamy kreske
   {
     //el[index] = '-';
     //index++;
     Serial.println("mamy kreske");
     el = String(el + "-");
   }
   if(time_held <= 2*kropka) // mamy kropke // w sumie mozna dac 3*kropka
   {
     //el[index] = '.';
     //index++;
     Serial.println("mamy kropke");
     el = String(el + ".");
   }
   
  }
}



String morse_to_letter(String morse)
{
    if(morse.compareTo(String(".-")) == 0 ) return String("a");
if(morse.compareTo(String("-...")) == 0 ) return String("b");
if(morse.compareTo(String("-.-.")) == 0 ) return String("c");
if(morse.compareTo(String("-..")) == 0 ) return String("d");
if(morse.compareTo(String(".")) == 0 ) return String("e");
if(morse.compareTo(String("..-.")) == 0 ) return String("f");
if(morse.compareTo(String("--.")) == 0 ) return String("g");
if(morse.compareTo(String("....")) == 0 ) return String("h");
if(morse.compareTo(String("..")) == 0 ) return String("i");
if(morse.compareTo(String(".---")) == 0 ) return String("j");
if(morse.compareTo(String("-.-")) == 0 ) return String("k");
if(morse.compareTo(String(".-..")) == 0 ) return String("l");
if(morse.compareTo(String("--")) == 0 ) return String("m");
if(morse.compareTo(String("-.")) == 0 ) return String("n");
if(morse.compareTo(String("---")) == 0 ) return String("o");
if(morse.compareTo(String(".--.")) == 0 ) return String("p");
if(morse.compareTo(String("--.-")) == 0 ) return String("q");
if(morse.compareTo(String(".-.")) == 0 ) return String("r");
if(morse.compareTo(String("...")) == 0 ) return String("s");
if(morse.compareTo(String("-")) == 0 ) return String("t");
if(morse.compareTo(String("..-")) == 0 ) return String("u");
if(morse.compareTo(String("...-")) == 0 ) return String("v");
if(morse.compareTo(String(".--")) == 0 ) return String("w");
if(morse.compareTo(String("-..-")) == 0 ) return String("x");
if(morse.compareTo(String("-.--")) == 0 ) return String("y");
if(morse.compareTo(String("--..")) == 0 ) return String("z");

return String("!");
  
}