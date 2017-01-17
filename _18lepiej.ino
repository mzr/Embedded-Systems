//linie oznaczone /**/ na początku mają być w kodzie dla odbierającego arduino, te bez dla nadającego
//ale czasem opisane w komentarzu jak a nie tym

#define diodPin 13
#define beepPin 9
#define kropka1 5 //2ms to juz za szybko
#define button 5 

byte ckropka = '.';
byte ckreska = '-';
byte cspacja = ' ';
byte cslash  = '/';

#define pojemnosc 300 //przy 500 i 73% zużycia pamięci na globalnych się wywala, co za beznadzieja...
byte tab[pojemnosc]; //100 to zdecydowanie za mało nadłuższe zdanie - i tak bardzo długie nie wejdzie
int przyjete = 0;
int wyslane = 0;

byte mozna_nowy_wlaczyc = 1;
byte swieci = 0;

int czas_czekania_po;
int czas_swiecenia;
long timenow;

int doWyslania = 0;



//nie ma czegoś takiego jak spacja między zdaniami, są symbole kropki itp.

String letter_to_morse(int letter) { //spacje nakońcu zapisu każdego znaku są ważne
    if(letter == 'a') return String(".- ");
    if(letter == 'b') return String("-... ");
    if(letter == 'c') return String("-.-. ");
    if(letter == 'd') return String("-.. ");
    if(letter == 'e') return String(". ");
    if(letter == 'f') return String("..-. ");
    if(letter == 'g') return String("--. ");
    if(letter == 'h') return String(".... ");
    if(letter == 'i') return String(".. ");
    if(letter == 'j') return String(".--- ");
    if(letter == 'k') return String("-.- ");
    if(letter == 'l') return String(".-.. ");
    if(letter == 'm') return String("-- ");
    if(letter == 'n') return String("-. ");
    if(letter == 'o') return String("--- ");
    if(letter == 'p') return String(".--. ");
    if(letter == 'q') return String("--.- ");
    if(letter == 'r') return String(".-. ");
    if(letter == 's') return String("... ");
    if(letter == 't') return String("- ");
    if(letter == 'u') return String("..- ");
    if(letter == 'v') return String("...- ");
    if(letter == 'w') return String(".-- ");
    if(letter == 'x') return String("-..- ");
    if(letter == 'y') return String("-.-- ");
    if(letter == 'z') return String("--.. ");
    if(letter == ' ') return String("/");
    if(letter == '1') return String(".---- ");
    if(letter == '2') return String("..--- ");
    if(letter == '3') return String("...-- ");
    if(letter == '4') return String("....- ");
    if(letter == '5') return String("..... ");
    if(letter == '6') return String("-.... ");
    if(letter == '7') return String("--... ");
    if(letter == '8') return String("---.. ");
    if(letter == '9') return String("----. ");
    if(letter == '0') return String("----- ");
    if(letter == '.') return String(".-.-.- ");
    if(letter == ',') return String("--..-- ");
    if(letter == '\'') return String(".----. ");
    if(letter == '"') return String(".-..-. ");
    if(letter == '_') return String("..--.- ");
    if(letter == ':') return String("---... ");
    if(letter == ';') return String("-.-.-. ");
    if(letter == '?') return String("..--.. ");
    if(letter == '!') return String("-.-.-- "); // lub --..--
    if(letter == '-') return String("-....- ");
    if(letter == '+') return String(".-.-. ");
    if(letter == '/') return String("-..-. ");
    if(letter == '(') return String("-.--. ");
    if(letter == ')') return String("-.--.- ");
    if(letter == '=') return String("-...- ");
    if(letter == '@') return String(".--.-. ");
    if(letter == 'ą') return String(".-.- ");
    if(letter == 'ć') return String("-.-.. ");
    if(letter == 'ę') return String("..-.. ");
    if(letter == 'ł') return String(".-..- ");
    if(letter == 'ń') return String("--.-- ");
    if(letter == 'ó') return String("---. ");
    if(letter == 'ś') return String("...-... ");
    if(letter == 'ż') return String("--..-. ");
    if(letter == 'ź') return String("--..- ");
    return String("");
}

void znak(int mult) {
    digitalWrite(diodPin,HIGH);
    czas_swiecenia = mult*kropka1;
    czas_czekania_po = kropka1;
    mozna_nowy_wlaczyc = 0;
    timenow = millis();
    swieci = 1;
    tone(beepPin,540);        
}

void blank(int mult) {
    czas_swiecenia = 0;
    czas_czekania_po = mult * kropka1;
    mozna_nowy_wlaczyc = 0;
    swieci = 0;
    timenow = millis();
}

/**/#define fotopin A5
/**/#define pmin 2
/**/#define pmax 4 //bo 3 coś ponoć źle z tone
/**/char kolejne[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
/**/                  '1','2','3','4','5','6','7','8','9','0',
/**/                  '.',',',"'",'"','_',':',';','?','!','-','+','/','(',')','=','@'/*,'ą','ć','ę','ł','ń','ó','ś','ż','ź'*/}; 
/**/ //miał problem z "\" bo znak spec., trza "\\"; ale tu nie ma; z " ' " ?
/**/
/**/String znaki[52] = 
/**/{
/**/String(".-"), //a
/**/String("-..."), //b
/**/String("-.-."), //c
/**/String("-.."), //d
/**/String("."), //e
/**/String("..-."), //f
/**/String("--."), //g
/**/String("...."), //h 
/**/String(".."), //i
/**/String(".---"), //j
/**/String("-.-"), //k
/**/String(".-.."), //l
/**/String("--"), //m
/**/String("-."), //n
/**/String("---"), //o
/**/String(".--."), //p
/**/String("--.-"), //q
/**/String(".-."), //r
/**/String("..."), //s
/**/String("-"), //t
/**/String("..-"), //u
/**/String("...-"), //v
/**/String(".--"), //w
/**/String("-..-"), //x
/**/String("-.--"), //y
/**/String("--.."), //z
/**/String(".----"), //1
/**/String("..---"),//2
/**/String("...--"),//3
/**/String("....-"),//4
/**/String("....."),//5
/**/String("-...."),//6
/**/String("--..."),//7
/**/String("---.."),//8
/**/String("----."),//9
/**/String("-----"),//0
/**/String(".-.-.-"),//.
/**/String("--..--"),//,
/**/String(".----."),// '
/**/String(".-..-."),//"
/**/String("..--.-"),//_
/**/String("---..."),//:
/**/String("-.-.-."),// ;
/**/String("..--.."),//?
/**/String("-.-.--"), //!   lub --..--
/**/String("-....-"), //-
/**/String(".-.-."),// +
/**/String("-..-."),// /
/**/String("-.--."),// (
/**/String("-.--.-"),// )
/**/String("-...-"),//=
/**/String(".--.-.") /*, //@
String(".-.-"),//ą
String("-.-.."),//ć
String("..-.."),//ę
String(".-..-"),//ł
String("--.--"),//ń
String("---."),//ó
String("...-..."),//ś
String("--..-."),//ż
String("--..-")//ź*/ //ASCII nie obsługuje pl, trzeba by jakoś inaczej
};

/**/int kropka = 5; //zrobić je jedną i tą samą
/**/int hold = 0;
/**/int released = 0;
/**/int lewy = 0, prawy = 1024;
/**/int nacisniecie;
/**/int czas_nacisniecia;
/**/
/**/long parse_time;
/**/long parsed; //psuło się przez przekręcanie
/**/
/**/String el = String("");
/**/String slowo = String("");
/**/String output = String(""); //on chyba nie obsługuje dłuższych niż ok. 70 znaków?! a może już mu się w pamięci nie mieści...
//po rozbiciu na dwa programy i dwa arduino powinno być lepiej

/**/int slowo_gotowe = 0;
/**/
/**/String morse_to_letter(String morse)
/**/{
/**/  Serial.println(morse);
/**/    for(int i=0; i<52; i++)
/**/      if(morse.compareTo(znaki[i]) == 0)
/**/        return String(kolejne[i]);
   /**/ 
/**/    //chyba niepotrzebne
/**/    if(morse.compareTo(String("")) == 0 ) return String("");
/**/
/**/    // gdy sie nie dopasowalo tzn nie ma takiego znaku
/**/    return String("*");
/**/}
/**/
/**/String kropka_czy_kreska(int time) {
/**/    if( time < 3*kropka )
/**/        return String(".");
/**/    if( time >= 3*kropka)
/**/        return String("-");
/**/}
/**/
/**/bool sprawdzaj(int pin) {
/**/  //Serial.println(analogRead(pin));
/**/  int mi=min(lewy, prawy);
/**/  int ma=max(lewy, prawy);
/**/  int wartosc=constrain(analogRead(pin), mi, ma);
/**/  return analogRead(pin)>(mi+ma)/2;
/**/}

/**/ //SETUP W ODBIERAJĄCYM 1-3 i 5. LINIE, w nadającym 1'szą i 4'tą tylko!
void setup() {
    Serial.begin(9600);   
    pinMode(pmin, INPUT_PULLUP);
    pinMode(pmax, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);
    pinMode(diodPin,OUTPUT);
}

/**/ //W LOOP TEŻ TE Z /**/ W ODBIERAJĄCYM
void loop() {
    if (Serial.available() > 0) {
        int incomingByte = Serial.read();
        //Serial.print(incomingByte);
        String a = letter_to_morse(incomingByte);

        for(int i=0; i<a.length(); i++) { //dokleja przetworzony na Morse'a znak
            tab[przyjete] = a[i];
            przyjete = ( przyjete + 1 ) % pojemnosc;
        }
                
        doWyslania += a.length();
                
        if(incomingByte == ckreska);
            //Serial.println("kreska");
        if(incomingByte == ckropka); 
            //Serial.println("koniec zdania");
        if(incomingByte == cspacja);
            //Serial.println("spacja");
    }
        
    if(mozna_nowy_wlaczyc && doWyslania > 0 ) { 
        if(tab[wyslane] == ckropka) 
            znak(1);
        if(tab[wyslane] == ckreska) 
            znak(3);
        if(tab[wyslane] == cspacja) 
            blank(2); //się dodaje do domyślnej jednokropkowej pauzy po każdym
        if(tab[wyslane] == cslash) 
            blank(6);//się dodaje do domyślnej jednokropkowej pauzy po każdym
    }
        
    if( millis() - timenow >= czas_swiecenia && swieci  && !mozna_nowy_wlaczyc ) {
        digitalWrite(diodPin,LOW);
        noTone(beepPin);
        swieci = 0;
    }
    if( millis() - timenow >= czas_swiecenia + czas_czekania_po && !swieci && !mozna_nowy_wlaczyc) {
        mozna_nowy_wlaczyc = 1;
        wyslane = ( wyslane + 1 ) % pojemnosc; 
        doWyslania--;
    }

    //pali diodę przez 3s i wtedy drugi ma nacisnąć pmax
    //pmin trzeba przy zwykłym oświetleniu a pmax przy zapalonej
    //jak się światło zmieni to kalibrować jeszcze raz
    //przy kalibracji uzna ze sie cos przeslalo pewnie, no ale trudno
    //można by jeszcze dodać przycisk ignorowania albo włącz/wyłącz
    if (digitalRead(button) == LOW)
    {
      //Serial.println("but");
      digitalWrite(diodPin,HIGH);
      delay(500);
      //!!! USUNĄĆ TO JAK NA DWA ARDUINO - tam się da przycisnąć i nie prześle się 'prawy'
      prawy = analogRead(fotopin); //!!! USUNĄĆ TO JAK NA DWA ARDUINO - tam się da przycisnąć i nie prześle się 'prawy'
      delay(3000);
      digitalWrite(diodPin,LOW);
      delay(500);
    }

  
/**/    int sensorVal = sprawdzaj(fotopin); //gdy puszczony to jest 1
/**/  
/**/    // on press
/**/    if(sensorVal == 0 && hold == 0) {
/**/        hold = 1;
/**/        released = 0;
/**/        //Serial.println("pressed");
/**/        nacisniecie = millis();
/**/        slowo_gotowe = 0; //ogarnia, że pauza się skończyła i będzie nowe słowo
/**/        
/**/    }
/**/  
/**/    // on release
/**/    if(sensorVal == 1 && hold == 1) {
/**/        hold = 0;
/**/        released = 1;
/**/        czas_nacisniecia = millis() - nacisniecie;
/**/        //Serial.println(czas_nacisniecia);
/**/        el += kropka_czy_kreska(czas_nacisniecia);
/**/        
/**/        parsed = millis();
/**/
/**/    }
/**/    
/**/    if(released) {
/**/       parse_time = millis() - parsed;
/**/       
/**/      if(parse_time <= kropka) {
/**/        //Serial.println(0);
/**/          //nic bo sie dodaje do znakow na puszczeniu przycisku 
/**/       }
/**/       if(parse_time > 2*kropka && parse_time <= 4*kropka) {
/**/       //Serial.println(1);
/**/           if( el.length() > 0 ) {
/**/            slowo += morse_to_letter(el);
/**/            //Serial.println(morse_to_letter(el));
/**/           }
/**/           el = String("");
/**/       }
/**/       if(parse_time > 4*kropka && parse_time <= 10*kropka) {
/**/        //Serial.println(slowo_gotowe);
/**/           if( slowo_gotowe == 0) { Serial.println(slowo); output += slowo; output+=' '; }
/**/           slowo = String("");
/**/           slowo_gotowe = 1; //po końcu słowa
/**/       }
/**/       if(parse_time > 10*kropka) {
/**/        //Serial.println(3);
/**/           Serial.print("##WIADOMOSC##: ");
/**/           Serial.println(output);
/**/            released = 0;   
/**/            output = String("");
/**/            slowo_gotowe = 0;
/**/       }
/**/  }
/**/  if (digitalRead(pmin) == LOW) //dla przycisków min, max nie patrzymy na drganie styków bo naciśnięcie kilka razy nic nie zmienia
/**/  {
/**/   //Serial.println("min");
/**/   lewy=analogRead(fotopin); //dla tej wartości nie świeci
/**/  }
/**/ 
/**/  if (digitalRead(pmax) == LOW) 
/**/  {
/**/    //Serial.println("max");
/**/    prawy=analogRead(fotopin);
/**/  }
}


