

#define r 9
#define g 10
#define b 11

bool czynowa = true;
long wr,wg,wb;
long pwmteraz;
long czyrosnie;
int przyrost = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(r,OUTPUT);
  analogWrite(r,200); //ok z tym, żeby później było analog
  pinMode(g,OUTPUT);
  analogWrite(g,200);
  pinMode(b,OUTPUT);
  analogWrite(b,200);

  randomSeed(analogRead(5));
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (czynowa)
  {
    wr=random(0,256);
    wg=random(0,256);
    wb=random(0,256);
    czynowa = false;
    pwmteraz=0;
    czyrosnie=1;
    pisz(pwmteraz, wr, wg, wb);
  }

  if (pwmteraz>0 || czyrosnie==1)
  {
    
    if (pwmteraz + przyrost*czyrosnie > 255)
    {
      pwmteraz = 255; //zrobimy tak, żeby świeciło na maksa, nawet jak nie trafi idealnie
      czyrosnie=-1;
    }
    else {
      pwmteraz += przyrost*czyrosnie;
    }
    pisz(pwmteraz, wr, wg, wb);
    delay(50);
  }
  else czynowa = 1;
  //pisz(pwmteraz, wr, wg, wb);
  //delay(300);
}

void pisz(int pwm, int wr, int wg, int wb) //jak by np. r, to może być problem z #def'em
{
  analogWrite(r,(255-((pwm)*wr)/256));
  analogWrite(g,(255-((pwm)*wg)/256));
  analogWrite(b,(255-((pwm)*wb)/256));
}

//i podłączenia nieco inne - jedno do plusa, przez 3 pozostałę do pwm, im więcej pwm tym mniej świeci
