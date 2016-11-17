#define btnPin 2
#define diodPin 7
#define beepPin 9

int kropka = 1000;

int tolerancja = 10;

int time_press;
int hold = 0;
int time_held;

int time_release;
int released = 0;
int time_unheld;

String el = String(""); 
String znak = String("");

void setup() {
    Serial.begin(9600);
    pinMode(btnPin, INPUT_PULLUP);
    pinMode(diodPin, OUTPUT);
}

void loop() {
  int sensorVal = digitalRead(btnPin); //gdy puszczony to jest 1
  
    // on press
    if(sensorVal == 0 && hold == 0) {
        hold = 1;
        time_press = millis();
        
        if(released == 1) {
            time_unheld = millis() - time_release;

            //to znaczy ze to co bylo to byl el znaku
            if(time_unheld <= 2*kropka)
                Serial.println("to element znaku");
            // z tablicy el robimy litere
            if(time_unheld > 2*kropka && time_unheld <= 5*kropka ) {
                Serial.println("to literka");
                znak = String(znak + morse_to_letter(el));
                Serial.println(morse_to_letter(el));
                el = String("");
            }
            if(time_unheld > 5*kropka) {
                Serial.println("to slowo");
                znak = String(znak + " ");
                Serial.println(znak);
                znak = String(""); 
            }
        }
        released = 0;
    }
  
    // on release
    if(sensorVal == 1 && hold == 1) {
        hold = 0;
        time_held = millis() - time_press;  
        released = 1;
        time_release = millis();
   
        //mamy kreske
        if(time_held >= 3*kropka) {
            Serial.println("mamy kreske");
            el = String(el + "-");
        }
        // mamy kropke // w sumie mozna dac 3*kropka
        if(time_held <= 2*kropka) {
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