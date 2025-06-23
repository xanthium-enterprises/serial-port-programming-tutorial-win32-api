
void setup() 
{
  Serial.begin(9600); // Start serial communication at 9600 baud
  Serial.flush();     // Clear out going TX buffer first

  while (!Serial) { ; } // Wait for serial port to connect (for Leonardo/Micro/Zero)

  Serial.println("Hello from Arduino! to Windows 11 PC "); // Send message to PC once 
 
}

void loop() 
{
  
}
