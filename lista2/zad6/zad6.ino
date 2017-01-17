#define btnPin 2
#define diodPin 7
#define beepPin 9


/*
ponizej 3*kropka czasu nacisniecie mamy kropke
powyżej 3*kropka czasu nacisniecia mamy kreske

ponizej kropka czasu puszczenia mamy el. znaku
powyżej kropka a poniżej 3*kropka czasu puszczenia elementy znaku są zamieniane na znak
powyżej 3*kropka a poniżej 7*kropka czasu puszczenia znaki są zamieniane na slowo
powyżej 7*kropka czasu puszczenia automatycznie wypisywane jest slowo
*/
String tab[26] = 
{
String(".-"), //a
String("-..."), //b
String("-.-."), //c
String("-.."), //d
String("."), //e
String("..-."), //f
String("--."), //g
String("...."), //h 
String(".."), //i
String(".---"), //j
String("-.-"), //k
String(".-.."), //l
String("--"), //m
String("-."), //n
String("---"), //o
String(".--."), //p
String("--.-"), //q
String(".-."), //r
String("..."), //s
String("-"), //t
String("..-"), //u
String("...-"), //v
String(".--"), //w
String("-..-"), //x
String("-.--"), //y
String("--..") //z
};

int kropka = 200;

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
        //Serial.println("pressed");
        nacisniecie = millis();
        
        if(slowo_gotowe) {
          Serial.print("slowo: ");
            Serial.println(output);
            output = String("");
            slowo_gotowe = 0;
        }
        tone(beepPin,540);
        digitalWrite(diodPin,HIGH);
    }
  
    // on release
    if(sensorVal == 1 && hold == 1) {
        hold = 0;
        released = 1;
        czas_nacisniecia = millis() - nacisniecie;
        //Serial.println(czas_nacisniecia);
        el += kropka_czy_kreska(czas_nacisniecia);
        
        parse = millis();

        noTone(beepPin);
        digitalWrite(diodPin,LOW);
    }
    
    if(released) {
       parse_time = millis() - parse;
       
       if(parse_time <= kropka) {
          //nic bo sie dodaje do znakow na puszczeniu przycisku 
       }
       if(parse_time > kropka && parse_time <= 3*kropka) {
           slowo += morse_to_letter(el);
           if( el.length() > 0 )
           Serial.println(morse_to_letter(el));
           el = String("");
       }
       if(parse_time > 3*kropka && parse_time <= 7*kropka) {
           output += slowo;
           slowo = String("");
           int slowo_gotowe = 1;
       }
       if(parse_time > 7*kropka) {
           Serial.print("slowo: ");
           Serial.println(output);
            released = 0;   
            output = String("");
            slowo_gotowe = 0;
       }
    }
}

String morse_to_letter(String morse)
{
    for(int i=0; i<26; i++)
      if(morse.compareTo(tab[i]) == 0)
        return String((char)('a' + i));
    
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
