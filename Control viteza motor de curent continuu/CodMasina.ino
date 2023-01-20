
#include "TimerOne.h"

int intrare1 = 6; 
int intrare2 = 4; 
int en = 5;


int MOTOR = 3;  
unsigned int counter = 0;
long referinta = 40;
float c[3] = {0, 0, 0};
float e[3] = {0, 0, 0};
int loopCounter = 0;
float rotatie;
float rot_filtrat[2] = {0,0};


float diskslots = 20;  // Numarul orificilor din rotita



String msg;

void ISR_count2()  
{
  counter++;  // incrementeaza valoarea counterului pentru Motor
} 

void ISR_timerone()
{
  Timer1.detachInterrupt();  // Opreste timerul

  rotatie = (counter / diskslots) * 60.00;  // calculeaza Rotatiile/Minut pentru Motor
  //Serial.println(rotation2);  
  
  counter = 0;  //  reseteaza counterul
  Timer1.attachInterrupt( ISR_timerone );  // Enable the timer
}

void setup() {
    Serial.begin(115200);
    Timer1.initialize(100000); // set timer for 1sec
  
    attachInterrupt(digitalPinToInterrupt (MOTOR), ISR_count2, RISING);  // Increase counter when speed sensor pin goes High
    Timer1.attachInterrupt( ISR_timerone ); // Enable the timer
    pinMode (en, OUTPUT) ;
    pinMode (intrare1, OUTPUT);
    pinMode (intrare2, OUTPUT);
  
}



void loop() 
{
  loopCounter ++;
  referinta = 40; 
  rot_filtrat[0] = 0.015 * rotatie + 0.985 * rot_filtrat[1];
  e[0] = referinta - rot_filtrat[0]; //semnalul de eroare este iesirea - referinta
  c[0] =4.612*e[1] - 4.387*e[2] + 1.607*c[1] - 0.6065*c[2];
 //c[0] = 2.121*e[1] - 2.018*e[2] + 1.607*c[1] - 0.6065*c[2];
 //c[0] = -51.54*e[1] + 0.8187*c[1];
  if(c[0] > 255) c[0] = 255;
  if(c[0] < 0) c[0] = 0;
  digitalWrite(intrare1, LOW);
  digitalWrite(intrare2, HIGH);

  analogWrite(en, c[0]);

  if(loopCounter == 3000){
  Serial.print("Acum motorul se roteste cu ");
  Serial.print(rot_filtrat[0]);
  Serial.println(" RPM");
  Serial.println();
  Serial.print("Semnalul de comanda este ");
  Serial.print(c[0]);
  Serial.println();
  Serial.print("Semnalul de eroare este ");
  Serial.print(e[0]);
  Serial.println();
  Serial.print("Referinta este ");
  Serial.print(referinta);
  Serial.println();
  loopCounter = 0;
  }
  
   for(int i=2;i>0;i--)
    {
      c[i]=c[i-1];
      e[i]=e[i-1];
    }
    rot_filtrat[1]=rot_filtrat[0];
}  
