#define diodPin 13
#define beepPin 8

#define kropka 50;

byte ckropka = '.';
byte ckreska = '-';
byte cspacja = ' ';
byte cslash  = '/';

#define pojemnosc 100
byte tab[pojemnosc];
int przyjete = 0;
int wyslane = 0;

byte mozna_nowy_wlaczyc = 1;
byte swieci = 0;

int czas_czekania_po;
int czas_swiecenia;
long time;

int doWyslania = 0;

void setup() {
    Serial.begin(9600);   
    pinMode(diodPin,OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        int incomingByte = Serial.read();

        String a = letter_to_morse(incomingByte);

        for(int i=0; i<a.length(); i++) {
            tab[przyjete] = a[i];
            przyjete = ( przyjete + 1 ) % pojemnosc;
        }
                
        doWyslania += a.length();
                
        if(incomingByte == ckreska)
            Serial.println("kreska");
        if(incomingByte == ckropka)
            Serial.println("kropka");
        if(incomingByte == cspacja)
            Serial.println("spacja");
    }
        
    if(mozna_nowy_wlaczyc && doWyslania > 0 ) { 
        if(tab[wyslane] == ckropka) 
            znak(1);
        if(tab[wyslane] == ckreska) 
            znak(3);
        if(tab[wyslane] == cspacja) 
            blank(3);
        if(tab[wyslane] == cslash) 
            blank(4);
    }
        
    if( millis() - time >= czas_swiecenia && swieci  && !mozna_nowy_wlaczyc ) {
        digitalWrite(diodPin,LOW);
        noTone(beepPin);
        swieci = 0;
    }
    if( millis() - time >= czas_swiecenia + czas_czekania_po && !swieci && !mozna_nowy_wlaczyc) {
        mozna_nowy_wlaczyc = 1;
        wyslane = ( wyslane + 1 ) % pojemnosc; 
        doWyslania--;
    }      
}

String letter_to_morse(int letter) {
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
}

void znak(mult) {
    digitalWrite(diodPin,HIGH);
    czas_swiecenia = mult*kropka;
    czas_czekania_po = kropka;
    mozna_nowy_wlaczyc = 0;
    time = millis();
    swieci = 1;
    tone(beepPin,540);        
}

void blank(mult) {
    czas_swiecenia = 0;
    czas_czekania_po = mult * kropka;
    mozna_nowy_wlaczyc = 0;
    swieci = 0;
    time = millis();
}