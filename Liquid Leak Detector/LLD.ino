

//TODO:Conectar servo Motor 
//2 LED e 3 botão
int ledAlert[]={2,3,4};
int cPetroleo=A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0;i<=2;i++)
    pinMode(ledAlert[i],OUTPUT);
}

void loop() {
  for(int i=0;i<=2;i++)
    digitalWrite(ledAlert[i],LOW);  // put your main code here, to run repeatedly:
  int reading = analogRead(cPetroleo);
  concentracPetroleo(reading);
  delay(2000);
}

void concentracPetroleo(int leitura)
{
  Serial.println("\nConcentracao de petroleo:\n");
  Serial.println(leitura);
  rSinalLED(leitura);
} 
void rSinalLED(int level)
{
  for(int i=0;i<=2;i++)
    digitalWrite(ledAlert[i],HIGH);
  compareLevel(level);
}
void compareLevel(int level)
{
  if(level<400)
  {
   //Nível Seguro
    digitalWrite(ledAlert[0],HIGH);
    for(int i =1 ; i<=2;i++)
      digitalWrite(ledAlert[i],LOW);
  }
  else if(level>=400 && level<800)
  {
    //Nível Médio
    digitalWrite(ledAlert[1],HIGH);
    digitalWrite(ledAlert[0],LOW);
    digitalWrite(ledAlert[2],LOW);
  }
  else
  {
    //Nível Crítico
    digitalWrite(ledAlert[2],HIGH);
    digitalWrite(ledAlert[0],LOW);
    digitalWrite(ledAlert[1],LOW);
  }
}

