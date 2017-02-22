#define dioda1 5
#define dioda2 6
#define dioda3 9
#define dioda4 10 //ponoć tone() może psuć pwm na pin'ie 11, tak piszą w reference
#define glosnik 3
int diody[]={0,5,6,9,10};

int czaspoprzdzwieku;
int zailecicho;
int czaspoprzdiody;
int coiledioda; //4 diody, więc to dzieli ilość szesnastek w zwrotce i nie ma reszty
int czasteraz;
int czekaj;

bool czygra;

int dl16 = 140;
char dzwieki[100];
int dl[100];
int iledzwiekow = 0;
int ilebylo = 0;
int trzydiody[4];

bool czywprawo = true;
int swieci = 1;



void dzwiek(char jaki, int czas)
{
  if ( jaki == 'a') tone(3, 220);
  if ( jaki == 'A') tone(3, 233); //wiem że to nie jest muzycznie poprawna nazwa, no ale kurczę...
  if ( jaki == 'h') tone(3, 247);
  if ( jaki == 'c') tone(3, 262);
  if ( jaki == 'C') tone(3, 277);
  if ( jaki == 'd') tone(3, 294);
  zailecicho = czas;
  czaspoprzdzwieku = millis();
  
}

void zapal() //zaczynamy od słabiej, żeby jak ktoraś dwa po kolei to nie osłabła
{
  analogWrite(diody[1], 0);
  analogWrite(diody[2], 0);
  analogWrite(diody[3], 0);
  analogWrite(diody[4], 0);
  analogWrite(diody[trzydiody[3]], 40);
  analogWrite(diody[trzydiody[2]], 120);
  analogWrite(diody[trzydiody[1]], 240);
}

void setup() {
  Serial.begin(9600);
  coiledioda = 2*dl16; //ma się zmieścić w 2 strony, czyli 8 zapaleń*2=16
  trzydiody[1]=1;
  trzydiody[2]=1;
  trzydiody[3]=1;
  czaspoprzdiody=millis();
  
  // put your setup code here, to run once:
  dzwieki[0]='C'; dl[0]=2*dl16; ++iledzwiekow;
  dzwieki[1]='d'; dl[1]=dl16; ++iledzwiekow;
  dzwieki[2]='C'; dl[2]=dl16; ++iledzwiekow;
  
  dzwieki[3]='C'; dl[3]=dl16; ++iledzwiekow;
  dzwieki[4]='d'; dl[4]=dl16; ++iledzwiekow;
  dzwieki[5]='C'; dl[5]=dl16; ++iledzwiekow;
  dzwieki[6]='C'; dl[6]=dl16; ++iledzwiekow;

  dzwieki[7]='d'; dl[7]=dl16; ++iledzwiekow;
  dzwieki[8]='C'; dl[8]=dl16; ++iledzwiekow;
  dzwieki[9]='C'; dl[9]=dl16; ++iledzwiekow;
  dzwieki[10]='C'; dl[10]=dl16; ++iledzwiekow;

  dzwieki[11]='c'; dl[11]=dl16; ++iledzwiekow;
  dzwieki[12]='C'; dl[12]=dl16; ++iledzwiekow;
  dzwieki[13]='C'; dl[13]=dl16; ++iledzwiekow;
  dzwieki[14]='C'; dl[14]=dl16; ++iledzwiekow;


  dzwieki[15]='h'; dl[15]=2*dl16; ++iledzwiekow;
  dzwieki[16]='c'; dl[16]=dl16; ++iledzwiekow;
  dzwieki[17]='h'; dl[17]=dl16; ++iledzwiekow;
  
  dzwieki[18]='h'; dl[18]=dl16; ++iledzwiekow;
  dzwieki[19]='c'; dl[19]=dl16; ++iledzwiekow;
  dzwieki[20]='h'; dl[20]=dl16; ++iledzwiekow;
  dzwieki[21]='h'; dl[21]=dl16; ++iledzwiekow;

  dzwieki[22]='c'; dl[22]=dl16; ++iledzwiekow;
  dzwieki[23]='h'; dl[23]=dl16; ++iledzwiekow;
  dzwieki[24]='h'; dl[24]=dl16; ++iledzwiekow;
  dzwieki[25]='h'; dl[25]=dl16; ++iledzwiekow;

  dzwieki[26]='A'; dl[26]=dl16; ++iledzwiekow;
  dzwieki[27]='h'; dl[27]=dl16; ++iledzwiekow;
  dzwieki[28]='h'; dl[28]=dl16; ++iledzwiekow;
  dzwieki[29]='h'; dl[29]=dl16; ++iledzwiekow;

  //te 2 zwrotki się powtarzają
}

void loop() {
  // put your main code here, to run repeatedly:

  czasteraz = millis();

  if (czasteraz-czaspoprzdiody >= coiledioda) {
    if (czywprawo) {
      zapal();
      trzydiody[3]=trzydiody[2];
      trzydiody[2]=trzydiody[1];
      trzydiody[1]=min(4,swieci+1);
      ++swieci; 
      if (swieci>4) {swieci=4; czywprawo=false;}
    } else {
      zapal();
      trzydiody[3]=trzydiody[2];
      trzydiody[2]=trzydiody[1];
      trzydiody[1]=max(1,swieci-1); 
      --swieci;
      if (swieci<1) {swieci=1; czywprawo=true;}
    }
    //Serial.print(trzydiody[1]);
    //Serial.print(trzydiody[2]);
    //Serial.print(trzydiody[3]);
    //Serial.println();
    czaspoprzdiody = millis();
  }
  
  if (ilebylo<iledzwiekow && (ilebylo==0 || czasteraz-czaspoprzdzwieku >= zailecicho)) {
    //noTone(glosnik); //to jest potrzebne tylko na różnych pinach, lub na końcu a na jednym znacznie pogarsza dźwięk
    //delay(0.05*dl16);
    dzwiek(dzwieki[ilebylo], dl[ilebylo]);
    ++ilebylo;
  }
  if (ilebylo == iledzwiekow) { /*noTone(glosnik); czygra = 0;*/ ilebylo=0; }
}
