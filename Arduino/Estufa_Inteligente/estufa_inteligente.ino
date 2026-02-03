// C++ code
//

int buzzer = 7;
int pinoTemp = A0;
int LED = 6;
int cooler = 5;
float tempLimiteCool = 30.0;
float tempLimite = 50.0;


void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(cooler,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
 int reading = analogRead(pinoTemp);

 float tension = reading * (5.0/1023);
 float tempC = (tension - 0.5)*100;
 
 Serial.print("Temperatura: ");
 Serial.print(tempC);
 Serial.println(" C");
 
 siren(tempC);
 air(tempC);

  delay(500);
}
void siren(float temp)
{
	if (temp >= tempLimite) 
 {
    //Barulho do buzzer
	tone(buzzer,700);
  	delay(300);
   	tone(buzzer,1200);
   	delay(300);
   
      //Piscar led
   	digitalWrite(LED,HIGH);
   	delay(300);
   	digitalWrite(LED,LOW);
 } 
  else 
 {
    digitalWrite(buzzer, LOW);
    noTone(buzzer);
    digitalWrite(LED,LOW);
 }

}
void air(float temp)
{
  if(temp>=tempLimiteCool)
  {
  	digitalWrite(cooler,HIGH);
  }
  else
  {
    digitalWrite(cooler,LOW);
  }
}
