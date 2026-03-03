// C++ code
//

//TODO: Organizar código

int button = 9;
int LED[] = {2, 3, 4, 5, 6, 7};
int numLED = 6;

void setup()
{
  pinMode(button, INPUT_PULLUP);
 
  for(int i =1; i<numLED; i++)
  	pinMode(LED[i], OUTPUT);
 
   randomSeed(analogRead(0));
}

void loop()
{
  if(digitalRead(button) == LOW) 
  {
  	sorteio();
  }
  
}
 void sorteio()
 {
 
   	delay(100);
  	if(digitalRead(button) == LOW) {
    

    	for(int i = 0; i < numLED; i++) {
      		digitalWrite(LED[i], LOW);
    	}

    
    	int sorteio = random(0, numLED);
     
   		digitalWrite(LED[sorteio], HIGH);
    
     	delay(100); 
   }
 
 }
