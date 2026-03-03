// C++ code
//


int LED = 5;
int button=4;
int motor = 3;
void setup()
{
  pinMode(button, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(motor, OUTPUT);
}

void loop()
{
  
  if(digitalRead(button)== HIGH)
  {
    	digitalWrite(LED, HIGH);
    	digitalWrite(motor, HIGH);
  }
  
  else
  	{
  		digitalWrite(LED, LOW);
    	digitalWrite(motor, LOW);
  		//delay(1000); // Wait for 1000 millisecond(s)
  	}
 }

