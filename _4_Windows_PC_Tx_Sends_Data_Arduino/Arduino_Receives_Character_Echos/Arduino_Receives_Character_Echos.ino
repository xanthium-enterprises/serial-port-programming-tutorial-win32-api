void setup() 
{
  Serial.begin(9600); // Start serial communication at 9600 baud
 
  while (!Serial) { ; } // Wait for serial port to connect (for Leonardo/Micro/Zero)

}

void loop() 
{
   if (Serial.available() > 0) 
   {
    
    char ReceivedChar = Serial.read();//Read data in the Buffer

    switch(ReceivedChar)
    {
      delay(3500);
      case 'A' : Serial.print("A");break;
      case 'B' : Serial.print("B");break;
      case 'C' : Serial.print("C");break;
      default  : Serial.print("?");
      
    }
    delay(500);
    
   }
}