//linie oznaczone /**/ na początku mają być w kodzie dla odbierającego arduino, te bez dla nadającego
//ale czasem opisane w komentarzu jak a nie tym


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

/**/int kropka = 3; //zrobić je jedną i tą samą
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
    
}

/**/ //W LOOP TEŻ TE Z /**/ W ODBIERAJĄCYM
void loop() {
    
  
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
/**/   Serial.println("min");
/**/   lewy=analogRead(fotopin); //dla tej wartości nie świeci
/**/  }
/**/ 
/**/  if (digitalRead(pmax) == LOW) 
/**/  {
/**/    Serial.println("max");
/**/    prawy=analogRead(fotopin);
/**/  }
}

