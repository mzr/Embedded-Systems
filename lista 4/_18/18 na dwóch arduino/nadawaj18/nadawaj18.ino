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




/**/ //SETUP W ODBIERAJĄCYM 1-3 LINIE, w nadającym 1'szą i 4-6 tylko!
void setup() {
    Serial.begin(9600);   
    //pinMode(pmin, INPUT_PULLUP);
    //pinMode(pmax, INPUT_PULLUP);
    pinMode(button, INPUT_PULLUP);
    pinMode(diodPin,OUTPUT);
    pinMode(beepPin,OUTPUT);
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
      //prawy = analogRead(fotopin); //!!! USUNĄĆ TO JAK NA DWA ARDUINO - tam się da przycisnąć i nie prześle się 'prawy'
      delay(3000);
      digitalWrite(diodPin,LOW);
      delay(500);
    }

  

}

