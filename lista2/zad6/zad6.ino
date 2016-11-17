#define btnPin 2
#define diodPin 7
#define beepPin 9

int kropka = 400;

int hold = 0;
int released = 0;

int nacisniecie;
int czas_nacisniecia;

int parse_time;
int parse;

String el = String("");
String slowo = String("");
String output = String("");

int slowo_gotowe = 0;

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
        released = 0;
        Serial.println("pressed");
        nacisniecie = millis();
        
        if(slowo_gotowe) {
            Serial.println(output);
            output = String("");
            slowo_gotowe = 0;
        }
    }
  
    // on release
    if(sensorVal == 1 && hold == 1) {
        hold = 0;
        released = 1;
        czas_nacisniecia = millis() - nacisniecie;
        Serial.println(czas_nacisniecia);
        el += kropka_czy_kreska(czas_nacisniecia);
        
        parse = millis();
    }
    
    if(released) {
       parse_time = millis() - parse;
       
       if(parse_time <= kropka) {
          //nic bo sie dodaje do znakow na puszczeniu przycisku 
       }
       if(parse_time > kropka && parse_time <= 3*kropka) {
           slowo += morse_to_letter(el);
           el = String("");
       }
       if(parse_time > 3*kropka && parse_time <= 7*kropka) {
           output += slowo;
           slowo = String("");
           int slowo_gotowe = 1;
       }
       if(parse_time > 7*kropka) {
           Serial.println(output);
            released = 0;   
            output = String("");
            slowo_gotowe = 0;
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
    
    //chyba niepotrzebne
    if(morse.compareTo(String("")) == 0 ) return String("");

    // gdy sie nie dopasowalo tzn nie ma takiego znaku
    return String("!");
}

String kropka_czy_kreska(int time) {
    if( time < 3*kropka )
        return String(".");
    if( time >= 3*kropka)
        return String("-");
}
