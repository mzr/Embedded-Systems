#define diod1 2
#define diod2 3
#define diod3 4
#define diod4 5
#define diod5 6

/*bool pic[][5] = {   {1,0,0,0,0},
                    {0,1,0,0,0},
                    {0,0,1,0,0},
                    {0,0,0,1,0},
                    {0,0,0,0,1},
                    {0,0,0,1,0},
                    {0,0,1,0,0},
                    {0,1,0,0,0},
                    {1,0,0,0,0},
                    {1,1,0,0,0},
                    {1,1,1,0,0},
                    {1,1,1,1,0},
                    {1,1,1,1,1},
                    {1,1,1,1,0},
                    {1,1,1,0,0},
                    {1,1,0,0,0},
                    {1,0,0,0,0},
                    {1,1,0,0,0},
                    {1,0,1,0,0},
                    {1,0,0,1,0},
                    {1,0,0,0,1},
                    {1,0,0,1,0},
                    {1,0,1,0,0},
                    {1,1,0,0,0},
                    {1,0,0,0,0},
                    {0,1,0,0,0},
                    {0,0,1,0,0},
                    {0,0,0,1,0},
                    {0,0,0,0,1},
                    {0,0,0,1,0},
                    {0,0,1,0,0},
                    {0,1,0,0,0}  };*/

bool pic[][5] = {   {1,0,0,0,0},
                    {0,1,0,0,0},
                    {0,0,1,0,0},
                    {0,0,0,1,0},
                    {0,0,0,0,1},
                    {0,0,0,1,0},
                    {0,0,1,0,0},
                    {0,1,0,0,0},
                    {1,0,0,0,0},
                    {1,1,0,0,0},
                    {1,1,1,0,0},
                    {1,1,1,1,0},
                    {1,1,1,1,1},
                    {1,1,1,1,0},
                    {1,1,1,0,0},
                    {1,1,0,0,0},
                    {1,0,0,0,0},
                    {1,1,0,0,0},
                    {1,0,1,0,0},
                    {1,0,0,1,0},
                    {1,0,0,0,1},
                    {1,0,0,1,0},
                    {1,0,1,0,0},
                    {1,1,0,0,0},
                    {1,0,0,0,0},
                    {0,1,0,0,0},
                    {0,0,1,0,0},
                    {0,0,0,1,0},
                    {0,0,0,0,1},
                    {0,0,0,1,0},
                    {0,0,1,0,0},
                    {0,1,0,0,0}  };

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
   pinMode(diod1, OUTPUT);
   pinMode(diod2, OUTPUT);
   pinMode(diod3, OUTPUT);
   pinMode(diod4, OUTPUT);
   pinMode(diod5, OUTPUT);

  digitalWrite(diod1,LOW);
  digitalWrite(diod2,LOW);
  digitalWrite(diod3,LOW);
  digitalWrite(diod4,LOW);
  digitalWrite(diod5,LOW);
}

int count = 0;

void loop() {
  // put your main code here, to run repeatedly:

  displayPic(count);  
  delay(2);
  count = (count+1)%(sizeof(pic)/5*sizeof(bool));
}

void displayPic(int count) {
  digitalWrite(diod1, pic[count][0]);
  digitalWrite(diod2, pic[count][1]);
  digitalWrite(diod3, pic[count][2]);
  digitalWrite(diod4, pic[count][3]);
  digitalWrite(diod5, pic[count][4]);
  Serial.print(pic[count][0]);
}


